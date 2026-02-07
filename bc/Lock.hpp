#ifndef BC_LOCK_HPP
#define BC_LOCK_HPP

#include "bc/lock/Atomic.hpp"
#include <cstdint>

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX) || defined(WHOA_SYSTEM_WEB)
#include <pthread.h>
#endif

namespace Blizzard {
namespace Lock {

// Types
#if defined(WHOA_SYSTEM_WIN)
typedef CRITICAL_SECTION Mutex;
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX) || defined(WHOA_SYSTEM_WEB)
typedef pthread_mutex_t Mutex;
#endif

struct DoOnceData {
    bool done;
    int32_t atomic;
};

// Functions
void DoOnce(DoOnceData& a1, void (*a2)(void*), void* a3);
int32_t MutexCreate(Mutex& mutex);
int32_t MutexEnter(Mutex& mutex);
int32_t MutexLeave(Mutex& mutex);

} // namespace Lock
} // namespace Blizzard

#endif
