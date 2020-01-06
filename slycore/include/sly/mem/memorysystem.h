#pragma once

#include <map>

#include "sly/global.h"
#include "sly/ext/plugin.h"
#include "sly/mem/heap.h"
#include "sly/mem/mallocheap.h"
#include "sly/mem/builders/memorymanagerbuilder.h"

namespace sly {
    class Kernel;
    class IMemorySystem  {
    public:
        typedef uint_t HeapId;
        virtual ~IMemorySystem() {}

        virtual retval<void> init(const MemorySystemDesc& desc) = 0;

        virtual vptr_t alloc(size_t ptr) = 0;        
        virtual void free(vptr_t ptr) = 0;

    protected:    
        IMemorySystem() {}
    };  

    class MemorySystem : public IMemorySystem {
    public:    
        MemorySystem(Kernel& kernel);
        virtual ~MemorySystem() {}

        virtual retval<void> init(const MemorySystemDesc& desc = MemorySystemBuilder().build()) { return success(); }

        virtual void getHeap(HeapId heapId) {}
        virtual void setHeap(HeapId heapId, IHeap& heap) {}
        virtual void removeHeap(HeapId heapId) {}

        virtual vptr_t alloc(size_t size) { return ::malloc(size); }       
        virtual void free(vptr_t ptr) { ::free(ptr); }

    protected:
        sly::Kernel& _kernel;
    
    };  
}