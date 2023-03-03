#include "bc/Process.hpp"
#include <ctime>

void Blizzard::Process::Sleep(uint32_t duration) {
#if defined(WHOA_SYSTEM_WIN)
    // TODO
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    struct timespec request;

    request.tv_sec = 0;
    request.tv_nsec = duration * 1000000;

    nanosleep(&request, nullptr);
#endif
}
