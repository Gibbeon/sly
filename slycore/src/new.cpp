#include "sly/global.h"
#include "sly/platform.h"
#include "sly/mem/memorymanager.h"

using namespace sly;

void *operator new(decltype(sizeof(0)) size) noexcept(false)
{
    return Platform::Memory().alloc(size);
}
void operator delete(void *ptr) throw()
{
    Platform::Memory().free(ptr);
}
void *operator new[](decltype(sizeof(0)) size) noexcept(false)
{
    return Platform::Memory().alloc(size);
}
void operator delete[](void *ptr) throw()
{
    Platform::Memory().free(ptr);
}
