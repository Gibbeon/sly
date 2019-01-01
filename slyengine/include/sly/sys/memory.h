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
            static inline void set(int value, void* dest, size_t size) { ::memset(dest, value, size); }
            template <typename T>
            static inline void fill(const T& value, T* buffer, size_t count)
            {
                for (size_t i = 0; i < count; ++i)
                    buffer[i] = value;
            }
    };

}