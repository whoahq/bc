#include "bc/String.hpp"
#include <cstring>

int32_t Blizzard::String::Copy(char* dst, const char* src, size_t len) {
    if (!len || !dst) {
        return 0;
    }

    if (!src) {
        *dst = 0;
        return 0;
    }

    char* v3 = dst + len - 1;

    char v4;
    const char* v5;
    char* v6;

    int32_t result;

    if (dst < v3 && (v4 = *src, v5 = src, v6 = dst, *src)) {
        do {
            *v6++ = v4;

            if (v3 <= v6) {
                break;
            }

            v4 = (v5++)[1];
        } while ( v4 );

        result = v6 - dst;
    } else {
        v6 = dst;
        result = 0;
    }

    *v6 = 0;

    return result;
}

uint32_t Blizzard::String::Length(const char* str) {
    if (str) {
        return strlen(str);
    }

    return 0;
}

void Blizzard::String::MemFill(void* dst, uint32_t len, uint8_t fill) {
    memset(dst, fill, len);
}
