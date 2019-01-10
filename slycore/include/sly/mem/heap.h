/* #pragma once

#include "sly/global.h"

class IHeapAllocator {
public:
    virtual ~IHeapAllocator() {}

    virtual vptr_t alloc(IHeap& heap, size_t size) = 0;
    virtual void free(IHeap& heap, vptr_t ptr) = 0;
protected:
    IHeapAllocator() {}
};

class IHeap {
public:
    virtual ~IHeap() {}

    virtual vptr_t head() = 0;
    virtual vptr_t tail() = 0;
    
    virtual vptr_t alloc(size_t size) = 0;
    virtual void free(vptr_t ptr) = 0;

    virtual size_t getSize() = 0;

protected:    
    IHeap() {}

};

 */