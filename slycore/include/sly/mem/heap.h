#pragma once

#include "sly/global.h"

namespace sly {
    class IHeap {
    public:
        virtual ~IHeap() {}
        
        virtual size_t getSize() = 0;
        
    protected:    
        IHeap() {}
    };  

    class Heap {
    public:
        Heap(vptr_t memory, size_t size);

        vptr_t head();
        vptr_t tail();
            
    protected:
    }

    // need to take alignment into consideration    
    class PoolAllocator {
    public:
        PoolAllocator(IHeap& heap, size_t blockSize); // blocksize should be a power of two ideally

        vptr_t alloc(size_t size) {
            // how many blocks do I need

            // search the table for that many blocks together (best fit, worst fit, first fit)

            // mark those blocks as allocated
            
            // calculate the return pointer

            return NULL;
        }

        void free(vptr_t ptr) {
            // get the table offset from the pointer
            
            // mark those blocks as free
        }

        // do we want the head of every pointer to be a pointer to it's heap?

        // getMaxAllocationSize();
        // getFreeSize();

    protected:
        IHeap& heap;
        size_t blockSize;
        size_t numBlocks;
        size_t offset;
    };

    class StackAllocator {
    public:
        StackAllocator(IHeap& heap); // blocksize should be a power of two ideally

        vptr_t alloc(size_t size) {
            // keep a pointer to next available
            // return next available

            return NULL;
        }

        void free(vptr_t ptr) {
            // you can only free the last ptr
            // move the pointer back by the size of this one
        }

        // do we want the head of every pointer to be a pointer to it's heap?

        // getMaxAllocationSize();
        // getFreeSize();

    protected:
        IHeap& heap;
    };

    class LinkedListAllocator { // doubly linked list perhaps? // maybe instead of blocks we still use a table of some sort?
    public:
        LinkedListAllocator(IHeap& heap, size_t blockSize); // blocksize should be a power of two ideally

        vptr_t alloc(size_t size) {
            // start at head, if used go to next allocation

            // if not used see if this can fit (best fit, worst fit, first fit)

            // mark those blocks as allocated
            
            // calculate the return pointer

            return NULL;
        }

        void free(vptr_t ptr) {
            // start at head, walk until ptr matches
            // set previous pointer to be the ptr of this
            // set new free size on previous pointer
            
            // mark those blocks as free
        }

        // do we want the head of every pointer to be a pointer to it's heap?

        // getMaxAllocationSize();
        // getFreeSize();

    protected:
        IHeap& heap;
    };
}