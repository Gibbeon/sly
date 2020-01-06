#include "sly/global.h"
/* #include "sly/engine.h"
#include "sly/mem/memorymanager.h"

using namespace sly;

void *operator new(decltype(sizeof(0)) size) noexcept(false)
{
    return Engine::MemorySystem().alloc(size);
}
void operator delete(void *ptr) throw()
{
    Engine::MemorySystem().free(ptr);
}
void *operator new[](decltype(sizeof(0)) size) noexcept(false)
{
    return Engine::MemorySystem().alloc(size);
}
void operator delete[](void *ptr) throw()
{
    Engine::MemorySystem().free(ptr);
}
 */

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        // this needs to be global
        #define __iscsym(_c) (isalnum(_c) || ((_c)=='_'))

        // Extra functions for MinGW. Most of these are the _s functions which are in
        // the Microsoft Visual Studio C++ CRT.
        #define _TRUNCATE 0
        #define STRUNCATE 80

        int strncpy_s(char* dest, size_t dest_size, const char* source, size_t count) {
        //CHECK(source != nullptr);
        //CHECK(dest != nullptr);
        //CHECK_GT(dest_size, 0);

        if (count == _TRUNCATE) {
            while (dest_size > 0 && *source != 0) {
            *(dest++) = *(source++);
            --dest_size;
            }
            if (dest_size == 0) {
            *(dest - 1) = 0;
            return STRUNCATE;
            }
        } else {
            while (dest_size > 0 && count > 0 && *source != 0) {
            *(dest++) = *(source++);
            --dest_size;
            --count;
            }
        }
        //CHECK_GT(dest_size, 0);
        *dest = 0;
        return 0;
        }
        
    #endif
#endif 