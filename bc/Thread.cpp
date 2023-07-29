#include "bc/Thread.hpp"
#include "bc/Debug.hpp"
#include "bc/system/System_Thread.hpp"

void Blizzard::Thread::AllocateLocalStorage(TLSSlot* slot) {
    System_Thread::AllocateLocalStorage(slot, nullptr);
}

void* Blizzard::Thread::RegisterLocalStorage(TLSSlot* slot, void* (*constructor)(void*), void* userData, void (*destructor)(void*)) {
    if (!System_Thread::TLSSlotIsAllocated(slot) && !System_Thread::AllocateTLSSlot(slot, destructor)) {
        BLIZZARD_ASSERT(!"Unable to allocate thread-local storage");
    }

    auto value = System_Thread::InternalGetLocalStorage(slot);
    if (value) {
        return value;
    }

    value = constructor(userData);
    System_Thread::InternalSetLocalStorage(slot, value);

    return value;
}

void Blizzard::Thread::SetLocalStorage(const TLSSlot* slot, const void* value) {
    BLIZZARD_ASSERT(Blizzard::Thread::TLSSlotIsAllocated(slot));

    System_Thread::InternalSetLocalStorage(slot, value);
}

bool Blizzard::Thread::TLSSlotIsAllocated(const TLSSlot* slot) {
    return System_Thread::TLSSlotIsAllocated(slot);
}
