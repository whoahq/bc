#include "bc/Memory.hpp"
#include <storm/Memory.hpp>

void* Blizzard::Memory::Allocate(uint32_t bytes) {
    return SMemAlloc(bytes, __FILE__, __LINE__, 0x0);
}

void* Blizzard::Memory::Allocate(uint32_t bytes, uint32_t flags, const char* filename, uint32_t linenumber, const char* a5) {
    // TODO
    // - determine purpose of a5
    // - flags manipulation

    return SMemAlloc(bytes, filename, linenumber, flags);
}

void Blizzard::Memory::Free(void* ptr) {
    SMemFree(ptr);
}
