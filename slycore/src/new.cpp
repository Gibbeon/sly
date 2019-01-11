#include "sly/global.h"
#include "sly/platform.h"
#include "sly/mem/memorymanager.h"

using namespace sly;

void *operator new(decltype(sizeof(0)) size) noexcept(false)
{
    return Platform::MemoryManager().alloc(size);
}
void operator delete(void *ptr) throw()
{
    Platform::MemoryManager().free(ptr);
}
void *operator new[](decltype(sizeof(0)) size) noexcept(false)
{
    return Platform::MemoryManager().alloc(size);
}
void operator delete[](void *ptr) throw()
{
    Platform::MemoryManager().free(ptr);
}
