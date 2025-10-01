#ifndef BC_DEBUG_HPP
#define BC_DEBUG_HPP

#include "bc/system/System_Debug.hpp"
#include <cstdint>

#if defined(NDEBUG)
#define BLIZZARD_ASSERT(x) \
    (void)0
#else
#define BLIZZARD_ASSERT(x)                               \
    if (!(x)) {                                          \
        Blizzard::Debug::Assert(#x, __FILE__, __LINE__); \
    }                                                    \
    (void)0
#endif

namespace Blizzard {
namespace Debug {

// Functions
void Assert(const char* expr, const char* file, uint32_t line);
void SetAssertHandler(Blizzard::System_Debug::AssertCallback callback);

} // namespace Debug
} // namespace Blizzard

#endif
