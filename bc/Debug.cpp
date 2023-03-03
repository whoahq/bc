#include "bc/Debug.hpp"

void Blizzard::Debug::Assert(const char* a1, const char* a2, uint32_t a3) {
    if (System_Debug::s_assertCallback) {
        System_Debug::s_assertCallback(a1, "", a2, a3);
    }
}

void Blizzard::Debug::SetAssertHandler(Blizzard::System_Debug::AssertCallback callback) {
    System_Debug::s_assertCallback = callback;
}
