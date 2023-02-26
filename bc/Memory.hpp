#ifndef BC_MEMORY_HPP
#define BC_MEMORY_HPP

#include <cstdint>

namespace Blizzard {
namespace Memory {

// Functions
void* Allocate(uint32_t bytes);
void* Allocate(uint32_t bytes, uint32_t flags, const char* filename, uint32_t linenumber, const char* a5);
void Free(void* ptr);

} // namespace Memory
} // namespace Blizzard

#endif
