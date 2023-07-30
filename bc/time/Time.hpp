#ifndef BC_TIME_TIME_HPP
#define BC_TIME_TIME_HPP

#include "bc/time/Types.hpp"

#include <cstdint>

namespace Blizzard {
namespace Time {

int32_t ToUnixTime(Timestamp timestamp);

Timestamp FromUnixTime(int32_t unixTime);

// Win32 FILETIME to y2k
Timestamp FromWinFiletime(uint64_t winTime);

uint64_t ToWinFiletime(Timestamp y2k);

Timestamp GetTimestamp();

int32_t GetTimeElapsed(uint32_t start, uint32_t end);

Timestamp MakeTime(const TimeRec& date);

void BreakTime(Timestamp timestamp, TimeRec& date);

uint64_t Nanoseconds();

uint64_t Microseconds();

uint64_t Milliseconds();

uint64_t Seconds();

} // namespace Time
} // namespace Blizzard

#endif
