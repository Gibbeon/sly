#pragma once

#include <stdlib.h>
#include <cstring>

#include "sly/global.h"

namespace sly {

    class Memory
    {
        public:
            static inline void* allocate(size_t size) { return ::malloc(size); }
            static inline void free(void* ptr) { ::free(ptr); }
            static inline void copy(const void* src, void* dest, size_t size) { ::memcpy(dest, src, size); }
    };

}