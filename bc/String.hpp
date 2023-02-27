#ifndef BC_STRING_HPP
#define BC_STRING_HPP

#include <cstdint>
#include <cstdlib>

namespace Blizzard {
namespace String {

// Functions
int32_t Copy(char* dst, const char* src, size_t len);
uint32_t Length(const char* str);
void MemFill(void* dst, uint32_t len, uint8_t fill);

} // namespace String
} // namespace Blizzard

#endif
