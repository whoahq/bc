#ifndef BC_SYSTEM_LOCK_HPP
#define BC_SYSTEM_LOCK_HPP

#include "bc/Lock.hpp"

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
#include <pthread.h>
#endif

namespace Blizzard {
namespace System_Lock {

// Types
#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
typedef pthread_mutexattr_t MutexAttr;
#endif

// Variables
#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
extern Lock::DoOnceData s_initMutexAttrOnce;
extern MutexAttr s_mutexattr;
#endif

// Functions
void InitAttr(void* a1);

} // namespace System_Lock
} // namespace Blizzard

#endif
