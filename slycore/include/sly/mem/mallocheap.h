#pragma once

#include <cstdint>
#include <cstdlib>

#include "sly/global.h"
#include "sly/mem/heap.h"

namespace sly {
    namespace mem {
        class MallocHeap : public IHeap {
        public:      
            MallocHeap() {}
            virtual ~MallocHeap() {}
                     
            virtual vptr_t alloc(size_t size) { return ::malloc(size); }
            virtual void free(vptr_t ptr) { ::free(ptr); }

            virtual size_t getSize() { return SIZE_MAX; }            
            virtual size_t getFreeSize() { return SIZE_MAX; }            
            virtual size_t getMaxAllocationSize() { return SIZE_MAX; }
        protected:
        };
    }
}