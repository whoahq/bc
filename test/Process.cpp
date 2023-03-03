#include "bc/Process.hpp"
#include "test/Test.hpp"

TEST_CASE("Blizzard::Process::Sleep", "[process]") {
    SECTION("sleeps") {
        Blizzard::Process::Sleep(1);
        SUCCEED();
    }
}
