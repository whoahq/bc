#include "bc/Thread.hpp"
#include "bc/Memory.hpp"
#include "test/Test.hpp"

void* ConstructInteger(void* value) {
    auto ptr = reinterpret_cast<int32_t*>(Blizzard::Memory::Allocate(sizeof(int32_t)));
    *ptr = *reinterpret_cast<int32_t*>(value);
    return ptr;
}

TEST_CASE("Blizzard::Thread::RegisterLocalStorage", "[thread]") {
    SECTION("constructs value and stores it in available TLS slot") {
        Blizzard::Thread::TLSSlot slot {};
        Blizzard::Thread::AllocateLocalStorage(&slot);

        int32_t value = 12345;
        auto ptr = Blizzard::Thread::RegisterLocalStorage(&slot, ConstructInteger, &value, nullptr);

        REQUIRE(*reinterpret_cast<int32_t*>(ptr) == value);
    }
}
