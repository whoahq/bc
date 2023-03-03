#ifndef BC_THREAD_HPP
#define BC_THREAD_HPP

#include <cstdint>

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
#include <pthread.h>
#endif

namespace Blizzard {
namespace Thread {

// Types
struct ThreadRecord {
#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    pthread_t unk0;
#endif
    void* unk4;
    uint32_t (*unk8)(void*);
    int32_t unkC;
    int32_t unk10;
    char name;
};

struct TLSSlot {
#if defined(WHOA_SYSTEM_WIN)
    uint32_t key;
#elif defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    pthread_key_t key;
#endif
    void (*destructor)(void*);
    bool allocated;
};

// Functions
void AllocateLocalStorage(TLSSlot* slot);
void* RegisterLocalStorage(TLSSlot* slot, void* (*constructor)(void*), void* userData, void (*destructor)(void*));
void SetLocalStorage(const TLSSlot* slot, const void* value);
bool TLSSlotIsAllocated(const TLSSlot* slot);

} // namespace Thread
} // namespace Blizzard

#endif
