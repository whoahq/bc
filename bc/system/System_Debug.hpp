#ifndef BC_SYSTEM_DEBUG_HPP
#define BC_SYSTEM_DEBUG_HPP

#include <cstdint>

namespace Blizzard {
namespace System_Debug {

// Types
typedef void (*AssertCallback)(const char* expr, const char* a2, const char* file, uint32_t line);

// Variables
extern AssertCallback s_assertCallback;

} // namespace System_Debug
} // namespace Blizzard

#endif
