#include "bc/lock/Atomic.hpp"

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#endif

int32_t Blizzard::Lock::Atomic::Increment(volatile int32_t* value) {
#if defined(WHOA_SYSTEM_WIN)
    return InterlockedIncrement(reinterpret_cast<volatile long*>(value));
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    return __sync_fetch_and_add(value, 1) + 1;
#endif
}
