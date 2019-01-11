#pragma once

#include "sly/global.h"

namespace sly {
    class IHeap {
    public:
        virtual ~IHeap() {}
        
        virtual vptr_t alloc(size_t size) = 0;
        virtual void free(vptr_t ptr) = 0;

        virtual size_t getSize() = 0;
        virtual size_t getFreeSize() = 0;
        virtual size_t getMaxAllocationSize() = 0;

    protected:    
        IHeap() {}
    };     
}