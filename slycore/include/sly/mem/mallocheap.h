#pragma once

#include <cstdint>
#include <cstdlib>

#include "sly/global.h"
#include "sly/mem/heap.h"

namespace sly {
        class MallocHeap : public IHeap {
        public:      
            MallocHeap() {}
            virtual ~MallocHeap() {}
                     
            virtual vptr_t alloc(size_t size) { return ::malloc(size); }
            virtual void free(vptr_t ptr) { ::free(ptr); }
            virtual void reset() {}
            virtual bool_t isInHeap(vptr_t ptr) { return true; }
            virtual vptr_t head() { return 0; }

            virtual size_t getSize() { return SIZE_MAX; }            
            virtual size_t getFreeSize() { return SIZE_MAX; }            
            virtual size_t getMaxAllocationSize() { return SIZE_MAX; }
        protected:
        };
    
}