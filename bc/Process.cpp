#include "bc/Process.hpp"

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
#include <ctime>
#endif

void Blizzard::Process::Sleep(uint32_t durationMs) {
#if defined(WHOA_SYSTEM_WIN)
    ::Sleep(durationMs);
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    struct timespec request;
    request.tv_sec = 0;
    request.tv_nsec = durationMs * 1000000;

    nanosleep(&request, nullptr);
#endif
}
