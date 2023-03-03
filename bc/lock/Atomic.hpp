#ifndef BC_LOCK_ATOMIC_HPP
#define BC_LOCK_ATOMIC_HPP

#include <cstdint>

namespace Blizzard {
namespace Lock {
namespace Atomic {

int32_t Increment(volatile int32_t* value);

} // namespace Atomic
} // namespace Lock
} // namespace Blizzard

#endif
