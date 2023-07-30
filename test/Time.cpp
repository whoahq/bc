#include "bc/Time.hpp"
#include "bc/time/TimeConst.hpp"
#include "bc/Process.hpp"
#include "test/Test.hpp"

TEST_CASE("Blizzard::Time::FromUnixTime", "[time]") {
    SECTION("convert zero Blizzard time from UNIX timestamp of Sat Jan 01 2000 00:00:00 GMT") {
        auto stamp = Blizzard::Time::FromUnixTime(946684800);
        REQUIRE(stamp == 0);
    }
}

TEST_CASE("Blizzard::Time::ToUnixTime", "[time]") {
    SECTION("convert zero Blizzard timestamp to Unix timestamp of Sat Jan 01 2000 00:00:00 GMT+0000") {
        auto stamp = Blizzard::Time::ToUnixTime(0);
        REQUIRE(stamp == 946684800);
    }
}

TEST_CASE("Blizzard::Time::GetTimestamp", "[time]") {
    SECTION("Get timestamp") {
        auto now = Blizzard::Time::GetTimestamp();
        REQUIRE(now > 0);
    }

    SECTION("Timestamp increases after 200 ms") {
        auto t1 = Blizzard::Time::GetTimestamp();
        Blizzard::Process::Sleep(200);
        auto t2 = Blizzard::Time::GetTimestamp();
        auto delta = t2 - t1;
        REQUIRE(t2 > t1);
        REQUIRE(delta >= 100000000);
    }
}

TEST_CASE("Blizzard::Time::Nanoseconds", "[time]") {
    SECTION("Read wall clock") {
        auto wctime = Blizzard::Time::Nanoseconds();
        REQUIRE(wctime > 0);
    }
}
