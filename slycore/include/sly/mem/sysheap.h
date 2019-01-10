/* #pragma once

#include "sly/global.h"

namespace sly {
    namespace mem {
        class SystemHeap : public IHeap {
        public:
            virtual vptr_t head() { return reinterpret_cast<vptr_t>(0); }
            virtual vptr_t tail() { return reinterpret_cast<vptr_t>(0); }
               
            virtual vptr_t alloc(size_t size) { return malloc(size); }
            virtual void free(vptr_t ptr) { free(ptr); }

            virtual size_t getSize() { return 0; }
        protected:
        };
    }
}
 */