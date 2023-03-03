#include "bc/Lock.hpp"
#include "test/Test.hpp"

TEST_CASE("Blizzard::Lock::Atomic::Increment", "[lock]") {
    SECTION("increments -1") {
        int32_t value = -1;
        REQUIRE(Blizzard::Lock::Atomic::Increment(&value) == 0);
    }

    SECTION("increments 0") {
        int32_t value = 0;
        REQUIRE(Blizzard::Lock::Atomic::Increment(&value) == 1);
    }
}

TEST_CASE("Blizzard::Lock::MutexCreate", "[lock]") {
    SECTION("creates mutex") {
        Blizzard::Lock::Mutex mutex1;
        REQUIRE(Blizzard::Lock::MutexCreate(mutex1) == 0);

        Blizzard::Lock::Mutex mutex2;
        REQUIRE(Blizzard::Lock::MutexCreate(mutex2) == 0);
    }
}

TEST_CASE("Blizzard::Lock::MutexEnter", "[lock]") {
    SECTION("enters and leaves mutex") {
        Blizzard::Lock::Mutex mutex;
        Blizzard::Lock::MutexCreate(mutex);

        int32_t mutexEntered = 0;

        Blizzard::Lock::MutexEnter(mutex);
        mutexEntered = 1;
        Blizzard::Lock::MutexLeave(mutex);

        REQUIRE(mutexEntered == 1);
    }
}
