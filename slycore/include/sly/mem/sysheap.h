#pragma once

#include <cstdint>
#include <cstdlib>

#include "sly/global.h"
#include "sly/mem/heap.h"

namespace sly {
    namespace mem {
        class SystemHeap : public IHeap {
        public:
            virtual vptr_t head() { return reinterpret_cast<vptr_t>(0); }
               
            virtual vptr_t alloc(size_t size) { return ::malloc(size); }
            virtual void free(vptr_t ptr) { ::free(ptr); }

            virtual size_t getSize() { return SIZE_MAX; }
        protected:
        };
    }
}