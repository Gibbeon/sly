#pragma once

#include "sly/global.h"
#include "sly/mem/memoryblock.h"
#include "sly/mem/allocator.h"

namespace sly {
    class IHeap {
    public:
        virtual ~IHeap() {}

        virtual vptr_t alloc(size_t) = 0;
        virtual void free(vptr_t) = 0;
        virtual void reset() = 0;

        virtual vptr_t head() = 0;
        virtual size_t getSize() = 0;

        virtual bool_t isInHeap(vptr_t) = 0;
        
    protected:    
        IHeap() {}
    };

    class Heap : public IHeap {
    public:
        Heap(MemoryBlock& block, IAllocator& allocator) :
            _block(block),
            _allocator(allocator)
        {
        }

        virtual ~Heap() {}

        virtual vptr_t alloc(size_t size) {
            return _allocator.alloc(size);
        }

        virtual void free(vptr_t ptr) {
            _allocator.free(ptr);
        }

        virtual void reset() {
            _allocator.reset();
        }

        virtual bool_t isInHeap(vptr_t ptr) {
            return ptr >= head() && ptr < tail();
        }
        
        virtual size_t getSize() {
            return _block.getSize();
        }

        virtual vptr_t head() {
            return _block.head();
        }

        vptr_t tail() {
            return (vptr_t)((size_t)head() + getSize());
        }

    protected:
        MemoryBlock& _block;
        IAllocator& _allocator;
    };
}