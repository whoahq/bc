#include "bc/system/System_Thread.hpp"
#include "bc/Debug.hpp"
#include "bc/Memory.hpp"
#include "bc/String.hpp"

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
#include <pthread.h>
#endif

bool Blizzard::System_Thread::s_initialized;
Blizzard::Thread::ThreadRecord* Blizzard::System_Thread::s_mainThread;
Blizzard::Lock::Mutex Blizzard::System_Thread::s_mutex;
Blizzard::Lock::Mutex Blizzard::System_Thread::s_registryMutex;
Blizzard::Thread::TLSSlot Blizzard::System_Thread::s_stackTraceEntryPointTLS;
Blizzard::Thread::TLSSlot Blizzard::System_Thread::s_threadRecordTLS;
std::map<Blizzard::Thread::ThreadRecord*, Blizzard::Thread::ThreadRecord*>* Blizzard::System_Thread::s_threadRegistry;
Blizzard::Thread::TLSSlot* Blizzard::System_Thread::s_slotList[128];
int32_t Blizzard::System_Thread::s_slotListUsed;

void Blizzard::System_Thread::AddToRegistry(Thread::ThreadRecord* thread) {
    Blizzard::Lock::MutexEnter(System_Thread::s_registryMutex);

    if (!System_Thread::s_threadRegistry) {
        auto m = Blizzard::Memory::Allocate(sizeof(std::map<Thread::ThreadRecord*, Thread::ThreadRecord*>), 0, __FILE__, __LINE__, nullptr);
        System_Thread::s_threadRegistry = new (m) std::map<Thread::ThreadRecord*, Thread::ThreadRecord*>();
    }

    System_Thread::s_threadRegistry->insert(std::pair<Thread::ThreadRecord*, Thread::ThreadRecord*>(thread, thread));

    Blizzard::Lock::MutexLeave(System_Thread::s_registryMutex);
}

bool Blizzard::System_Thread::AllocateLocalStorage(Thread::TLSSlot* slot, void (*destructor)(void*)) {
    System_Thread::InitThreadSystem();

    BLIZZARD_ASSERT(!System_Thread::TLSSlotIsAllocated(slot));

    if (!System_Thread::InternalAllocateLocalStorage(slot, destructor)) {
        BLIZZARD_ASSERT(!"failed to allocate TLS");
        return false;
    }

    slot->destructor = destructor;

    Blizzard::Lock::MutexEnter(System_Thread::s_mutex);

    System_Thread::s_slotList[System_Thread::s_slotListUsed] = slot;
    System_Thread::s_slotListUsed++;

    Blizzard::Lock::MutexLeave(System_Thread::s_mutex);

    return true;
}

bool Blizzard::System_Thread::AllocateTLSSlot(Thread::TLSSlot* slot, void (*destructor)(void*)) {
    System_Thread::InitThreadSystem();

    Blizzard::Lock::MutexEnter(System_Thread::s_mutex);

    auto result = false;

    if (System_Thread::TLSSlotIsAllocated(slot) || System_Thread::AllocateLocalStorage(slot, destructor)) {
        result = true;
    }

    Blizzard::Lock::MutexLeave(System_Thread::s_mutex);

    return result;
}

void Blizzard::System_Thread::InitThreadSystem() {
    if (System_Thread::s_initialized) {
        return;
    }

    System_Thread::s_initialized = true;

    Blizzard::Lock::MutexCreate(System_Thread::s_mutex);
    Blizzard::Lock::MutexCreate(System_Thread::s_registryMutex);

    Blizzard::Thread::AllocateLocalStorage(&System_Thread::s_threadRecordTLS);
    Blizzard::Thread::AllocateLocalStorage(&System_Thread::s_stackTraceEntryPointTLS);

    System_Thread::s_mainThread = System_Thread::NewThread(nullptr, nullptr, nullptr);
    Blizzard::Thread::SetLocalStorage(&System_Thread::s_threadRecordTLS, System_Thread::s_mainThread);

    System_Thread::s_mainThread->unkC = 1;
    System_Thread::s_mainThread->unk10 = 1;
}

bool Blizzard::System_Thread::InternalAllocateLocalStorage(Thread::TLSSlot* slot, void (*destructor)(void*)) {
#if defined(WHOA_SYSTEM_WIN)
    auto index = TlsAlloc();
    if (index == TLS_OUT_OF_INDEXES) {
        return false;
    }

    slot->key = index;
    slot->allocated = true;

    return true;
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    if (pthread_key_create(&slot->key, destructor)) {
        return false;
    }

    slot->allocated = true;
    return true;
#endif
}

void* Blizzard::System_Thread::InternalGetLocalStorage(const Thread::TLSSlot* slot) {
#if defined(WHOA_SYSTEM_WIN)
    return TlsGetValue(slot->key);
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    return pthread_getspecific(slot->key);
#endif
}

void Blizzard::System_Thread::InternalSetLocalStorage(const Thread::TLSSlot* slot, const void* value) {
#if defined(WHOA_SYSTEM_WIN)
    auto result = TlsSetValue(slot->key, const_cast<void*>(value));
    BLIZZARD_ASSERT(result);
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    auto err = pthread_setspecific(slot->key, value);
    BLIZZARD_ASSERT(err == 0);
#endif
}

Blizzard::Thread::ThreadRecord* Blizzard::System_Thread::NewThread(uint32_t (*a1)(void*), void* a2, const char* name) {
    if (!name) {
        name = "";
    }

    auto nameLen = Blizzard::String::Length(name);

    auto thread = static_cast<Blizzard::Thread::ThreadRecord*>(
        Blizzard::Memory::Allocate(sizeof(Blizzard::Thread::ThreadRecord) + nameLen + 1, 0, __FILE__, __LINE__, nullptr)
    );

    Blizzard::String::MemFill(thread, sizeof(Blizzard::Thread::ThreadRecord), 0);

    thread->unk4 = a2;
    thread->unk8 = a1;
    thread->unkC = 0;
    thread->unk10 = 2;

    Blizzard::String::Copy(&thread->name, name, nameLen + 1);

    System_Thread::AddToRegistry(thread);

    return thread;
}

bool Blizzard::System_Thread::TLSSlotIsAllocated(const Thread::TLSSlot* slot) {
    return slot->allocated;
}
