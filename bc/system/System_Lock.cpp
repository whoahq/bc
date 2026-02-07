#include "bc/system/System_Lock.hpp"

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX) || defined(WHOA_SYSTEM_WEB)
Blizzard::Lock::DoOnceData Blizzard::System_Lock::s_initMutexAttrOnce;
Blizzard::System_Lock::MutexAttr Blizzard::System_Lock::s_mutexattr;
#endif

void Blizzard::System_Lock::InitAttr(void* a1) {
#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX) || defined(WHOA_SYSTEM_WEB)
    pthread_mutexattr_init(&System_Lock::s_mutexattr);
    pthread_mutexattr_settype(&System_Lock::s_mutexattr, PTHREAD_MUTEX_RECURSIVE);
#endif
}
