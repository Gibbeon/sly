#pragma once

#include <stdlib.h>
#include <cstring>

#include "sly/global.h"

namespace sly {

    class Memory
    {
        public:
            static inline void* allocate(s32 size) { return ::malloc(size); }
            static inline void free(void* ptr) { ::free(ptr); }
            static inline void copy(const void* src, void* dest, s32 size) { ::memcpy(dest, src, size); }
    };

}