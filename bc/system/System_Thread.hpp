#ifndef BC_SYSTEM_THREAD_HPP
#define BC_SYSTEM_THREAD_HPP

#include "bc/Lock.hpp"
#include "bc/Thread.hpp"
#include <cstdint>
#include <map>

namespace Blizzard {
namespace System_Thread {

// Variables
extern bool s_initialized;
extern Thread::ThreadRecord* s_mainThread;
extern Lock::Mutex s_mutex;
extern Lock::Mutex s_registryMutex;
extern Thread::TLSSlot s_stackTraceEntryPointTLS;
extern Thread::TLSSlot s_threadRecordTLS;
extern std::map<Thread::ThreadRecord*, Thread::ThreadRecord*>* s_threadRegistry;
extern Thread::TLSSlot* s_slotList[128];
extern int32_t s_slotListUsed;

// Functions
void AddToRegistry(Thread::ThreadRecord* thread);
bool AllocateLocalStorage(Thread::TLSSlot* slot, void (*destructor)(void*));
bool AllocateTLSSlot(Thread::TLSSlot* slot, void (*destructor)(void*));
void InitThreadSystem();
bool InternalAllocateLocalStorage(Thread::TLSSlot* slot, void (*destructor)(void*));
void* InternalGetLocalStorage(const Thread::TLSSlot* slot);
void InternalSetLocalStorage(const Thread::TLSSlot* slot, const void* value);
Thread::ThreadRecord* NewThread(uint32_t (*a1)(void*), void* a2, const char* name);
bool TLSSlotIsAllocated(const Thread::TLSSlot* slot);

} // namespace System_Thread
} // namespace Blizzard

#endif
