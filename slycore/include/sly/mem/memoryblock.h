#pragma once

#include "sly/global.h"

namespace sly {
    class MemoryBlock {
    public:
        MemoryBlock(vptr_t head, size_t size);

        vptr_t head() { return _head; }
        vptr_t tail() { return reinterpret_cast<vptr_t>((size_t)_head + _size); }

        size_t getSize() { return _size; }
            
    protected:
        vptr_t _head;
        size_t _size;
    };
}