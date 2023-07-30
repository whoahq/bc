#ifndef BC_TIME_TYPES_HPP
#define BC_TIME_TYPES_HPP

#include <cstdint>

namespace Blizzard {
namespace Time {

// Timestamp - nanoseconds starting from 0 == January 1 2000 00:00:00 GMT.
typedef int64_t Timestamp;

class TimeRec {
    public:
        int32_t   year;
        uint32_t  month;
        uint32_t  day;
        uint32_t  hour;
        uint32_t  min;
        uint32_t  sec;
        uint32_t  nsec;
        uint32_t  wday;
        uint32_t  yday;
};

} // namespace Time
} // namespace Blizzard

#endif
