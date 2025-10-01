#include "bc/Debug.hpp"

void Blizzard::Debug::Assert(const char* expr, const char* file, uint32_t line) {
    if (System_Debug::s_assertCallback) {
        System_Debug::s_assertCallback(expr, "", file, line);
    }
}

void Blizzard::Debug::SetAssertHandler(Blizzard::System_Debug::AssertCallback callback) {
    System_Debug::s_assertCallback = callback;
}
