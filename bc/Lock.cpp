#include "bc/Lock.hpp"
#include "bc/Debug.hpp"
#include "bc/Process.hpp"
#include "bc/system/System_Lock.hpp"

void Blizzard::Lock::DoOnce(DoOnceData& a1, void (*a2)(void*), void* a3) {
    if (!a1.done) {
        if (Blizzard::Lock::Atomic::Increment(&a1.atomic) == 1) {
            a2(a3);
            a1.done = true;
        } else {
            while (!a1.done) {
                Blizzard::Process::Sleep(1);
            }
        }
    }
}

int32_t Blizzard::Lock::MutexCreate(Blizzard::Lock::Mutex& mutex) {
#if defined(WHOA_SYSTEM_WIN)
    InitializeCriticalSection(&mutex);

    return 0;
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    Blizzard::Lock::DoOnce(System_Lock::s_initMutexAttrOnce, System_Lock::InitAttr, nullptr);

    auto result = pthread_mutex_init(&mutex, &System_Lock::s_mutexattr);
    BLIZZARD_ASSERT(result == 0);

    return result;
#endif
}

int32_t Blizzard::Lock::MutexEnter(Blizzard::Lock::Mutex& mutex) {
#if defined(WHOA_SYSTEM_WIN)
    EnterCriticalSection(&mutex);

    return 0;
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    auto result = pthread_mutex_lock(&mutex);
    BLIZZARD_ASSERT(result == 0);

    return result;
#endif
}

int32_t Blizzard::Lock::MutexLeave(Blizzard::Lock::Mutex& mutex) {
#if defined(WHOA_SYSTEM_WIN)
    LeaveCriticalSection(&mutex);

    return 0;
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    auto result = pthread_mutex_unlock(&mutex);
    BLIZZARD_ASSERT(result == 0);

    return result;
#endif
}
