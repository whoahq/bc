#include "bc/Memory.hpp"
#include "test/Test.hpp"

TEST_CASE("Blizzard::Memory::Allocate", "[memory]") {
    SECTION("allocates memory and returns pointer") {
        auto ptr = Blizzard::Memory::Allocate(100);

        REQUIRE(ptr);

        Blizzard::Memory::Free(ptr);
    }

    SECTION("allocates memory and returns pointer using overload with flags") {
        auto ptr = Blizzard::Memory::Allocate(100, 0x0, __FILE__, __LINE__, nullptr);

        REQUIRE(ptr);

        Blizzard::Memory::Free(ptr);
    }
}
