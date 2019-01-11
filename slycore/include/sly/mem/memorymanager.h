#pragma once

#include "sly/global.h"
#include "sly/mem/heap.h"
#include "sly/mem/builders/memorymanagerbuilder.h"

namespace sly {
    class IMemoryManager : public IPlugin {
    public:
        virtual ~IMemoryManager() {}

        virtual void init(MemoryManagerDesc& desc);

        virtual IHeap& getGlobalHeap() = 0;
        virtual void setGlobalHeap(IHeap& hHandle) = 0;

        virtual void getHeap(size_t heapId) = 0;
        virtual void setHeap(size_t heapId, IHeap& heap) = 0;
        virtual void removeHeap(size_t heapId) = 0;

        virtual vptr_t alloc(size_t ptr) = 0;        
        virtual void free(vptr_t ptr) = 0;

    protected:    
        IMemoryManager() {}
    };  
}