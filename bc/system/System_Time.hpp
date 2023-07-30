#ifndef BC_SYSTEM_TIME_HPP
#define BC_SYSTEM_TIME_HPP

#include <cstdint>

#include "bc/time/Types.hpp"

namespace Blizzard {
namespace System_Time {

Time::Timestamp Now();

void CheckInit();

uint64_t QueryClockMoment();

uint64_t Nanoseconds();
uint64_t Microseconds();
uint64_t Milliseconds();
uint64_t Seconds();

} // namespace System_Time
} // namespace Blizzard

#endif
