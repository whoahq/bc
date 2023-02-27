#include "bc/String.hpp"
#include "test/Test.hpp"

TEST_CASE("Blizzard::String::Copy", "[string]") {
    SECTION("copies src to dst") {
        auto src = "abC";
        char dst[4] = { 0x11, 0x22, 0x33, 0x44 };

        Blizzard::String::Copy(dst, src, sizeof(dst));

        REQUIRE(dst[0] == 'a');
        REQUIRE(dst[1] == 'b');
        REQUIRE(dst[2] == 'C');
        REQUIRE(dst[3] == '\0');
    }
}

TEST_CASE("Blizzard::String::Length", "[string]") {
    SECTION("correctly determines length of 'abc'") {
        auto str = "abC";

        REQUIRE(Blizzard::String::Length(str) == 3);
    }
}

TEST_CASE("Blizzard::String::MemFill", "[string]") {
    SECTION("fills destination with given value") {
        char dst[3] = { 0x11, 0x22, 0x33 };

        Blizzard::String::MemFill(dst, sizeof(dst), 0x66);

        REQUIRE(dst[0] == 0x66);
        REQUIRE(dst[1] == 0x66);
        REQUIRE(dst[2] == 0x66);
    }
}
