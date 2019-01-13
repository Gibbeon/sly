/* #include "sly/global.h"
#include "sly/engine.h"
#include "sly/mem/memorymanager.h"

using namespace sly;

void *operator new(decltype(sizeof(0)) size) noexcept(false)
{
    return Engine::MemoryManager().alloc(size);
}
void operator delete(void *ptr) throw()
{
    Engine::MemoryManager().free(ptr);
}
void *operator new[](decltype(sizeof(0)) size) noexcept(false)
{
    return Engine::MemoryManager().alloc(size);
}
void operator delete[](void *ptr) throw()
{
    Engine::MemoryManager().free(ptr);
}
 */