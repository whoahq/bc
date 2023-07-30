#include "bc/system/System_Time.hpp"
#include "bc/time/Time.hpp"
#include "bc/time/TimeConst.hpp"

#if defined(WHOA_SYSTEM_MAC)
#include <mach/mach_time.h>
#endif

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
#include <ctime>
#include <sys/time.h>
#endif

#include "bc/Debug.hpp"

namespace Blizzard {
namespace System_Time {

// Globals

// Stores the earliest TSC value
static uint64_t s_absBegin = 0;

// Stores the number of nanoseconds since Jan 1, 2000 00:00 GMT at the raw clock moment of s_absBegin.
static Time::Timestamp s_gmBegin = 0;

// timeScales can be multiplied against number of ticks since s_absBegin to get
// meaningful durations in the corresponding format
double timeScaleNanoseconds  = 0.0;
double timeScaleMicroseconds = 0.0;
double timeScaleMilliseconds = 0.0;
double timeScaleSeconds      = 0.0;

// Functions

bool ReadTSC(uint64_t& counter) {
#if defined(WHOA_SYSTEM_WIN)
    LARGE_INTEGER li;
    auto ok = QueryPerformanceCounter(&li);

    if (ok) {
        counter = static_cast<uint64_t>(li.QuadPart);
        return true;
    }

    return false;
#elif defined(WHOA_SYSTEM_MAC)
    counter = mach_absolute_time();
    return true;
#elif defined(WHOA_SYSTEM_LINUX)
    struct timespec ts;
    auto status = clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    if (status == 0) {
        counter = (static_cast<uint64_t>(ts.tv_sec) * TimeConst::TimestampsPerSecond) + ts.tv_nsec;
        return true;
    }
    return false;
#endif
}

// Returns a clock moment, relative to s_absBegin;
uint64_t QueryClockMoment() {
    uint64_t counter = 0;
    ReadTSC(counter);

    return counter - s_absBegin;
}

// Returns Y2K-GMT nanosecond time.
Time::Timestamp Now() {
    CheckInit();

    // Record clock moment
    auto moment = QueryClockMoment();

    // Add moment to GMT
    return s_gmBegin + static_cast<Time::Timestamp>(timeScaleNanoseconds * static_cast<double>(moment));
}

// this func is run on first use
void TimeInit() {
    // Record absolute clock beginning moment in raw CPU time
    ReadTSC(s_absBegin);
    BLIZZARD_ASSERT(s_absBegin != 0);

    // Look at system clock's GMT/UTC time as nanoseconds
    // This associates a point in GMT with the more precise measurements obtained from reading the timestamp counter
#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    // Unix system clock
    struct timeval tv;
    gettimeofday(&tv, nullptr);

    s_gmBegin = Time::FromUnixTime(tv.tv_sec) + (tv.tv_usec * 1000ULL);
#elif defined(WHOA_SYSTEM_WIN)
    // Read Win32 system time
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);

    // Convert time into Blizzard timestamp
    ULARGE_INTEGER ul = {};
    ul.HighPart = ft.dwHighDateTime;
    ul.LowPart  = ft.dwLowDateTime;
    s_gmBegin = Time::FromWinFiletime(ul.QuadPart);
#endif

    // Attempt to figure out the scale of TSC durations in real-time
#if defined(WHOA_SYSTEM_WIN)
    // Read frequency with Win32 API
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    auto ticksPerSecond       = static_cast<uint64_t>(freq.QuadPart);
    auto ticksPerNanosecond   = static_cast<double>(ticksPerSecond) / static_cast<double>(TimeConst::TimestampsPerSecond);

    timeScaleNanoseconds = 1.0 / ticksPerNanosecond;
#elif defined(WHOA_SYSTEM_MAC)
    // Ask Mach what the base time parameters are
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);

    timeScaleNanoseconds = static_cast<double>(timebase.numer) / static_cast<double>(timebase.denom);
#elif defined(WHOA_SYSTEM_LINUX)
    // clock_gettime is already attuned to timestamp counter frequency
    timeScaleNanoseconds = 1.0;
#endif
    timeScaleMicroseconds = timeScaleNanoseconds / 1000.0;
    timeScaleMilliseconds = timeScaleNanoseconds / 1000000.0;
    timeScaleSeconds      = timeScaleNanoseconds / 1000000000.0;
}

void CheckInit() {
    if (s_absBegin == 0) {
        TimeInit();
    }
}

// Wall clock functions. The values returned are of an arbitrary epoch.
// The only guarantee is that the values returned will increase monotonically.

// Get wall clock time in nanoseconds
uint64_t Nanoseconds() {
    CheckInit();
    uint64_t tsc;
    ReadTSC(tsc);
    return static_cast<uint64_t>(static_cast<double>(tsc) * timeScaleNanoseconds);
}

// Get wall clock time in microseconds
uint64_t Microseconds() {
    CheckInit();
    uint64_t tsc;
    ReadTSC(tsc);
    return static_cast<uint64_t>(static_cast<double>(tsc) * timeScaleMicroseconds);
}

// Get wall clock time in milliseconds
uint64_t Milliseconds() {
    CheckInit();
    uint64_t tsc;
    ReadTSC(tsc);
    return static_cast<uint64_t>(static_cast<double>(tsc) * timeScaleMilliseconds);
}

// Get wall clock time in seconds
uint64_t Seconds() {
    CheckInit();
    uint64_t tsc;
    ReadTSC(tsc);
    return static_cast<uint64_t>(static_cast<double>(tsc) * timeScaleSeconds);
}

} // namespace System_Time
} // namespace Blizzard
