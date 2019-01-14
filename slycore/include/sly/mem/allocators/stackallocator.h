#pragma once

#include "sly/global.h"

namespace sly {
    template<size_t alignment = 64>
    class StackAllocator : public IAllocator {
    private:
        struct AllocEntry {
            union {
                u32 size;
                _padding[static_log2<alignment>()];
            };
        };
    public:
        StackAllocator(IHeap& heap) :
            _heap(heap) 
        {
        }

        void reset() {
            _current = reinterpret_cast<AllocEntry*>(_heap.head());
            _current->size = 0;
        }

        vptr_t alloc(size_t size) {
            // the result is current + the header space
            vptr_t result = reinterpret_cast<vptr_t>((size_t)_current + sizeof(AllocEntry));

            // align allocation
            size = ((size + sizeof(AllocEntry)) >> static_log2<alignment>()) << static_log2<alignment>();

            // set current to new spot
            _current = reinterpret_cast<AllocEntry*>((size_t)_current + size);

            // set size of the previous pointer, such that _current - (size + reinterpret_cast<AllocEntry*>()
            _current->size = size;

            return result;
        }

        void free(vptr_t ptr) {
            // this basically frees back to the ptr
            _current = ptr - sizeof(AllocEntry);
            _current->size = 0;
        }

        void pop() {
            // frees the last allocation
            _current = (size_t)_current - _current->size;
            _current->size = 0;
        }

    protected:
        IHeap& _heap;
        AllocEntry* _current;
    };
}