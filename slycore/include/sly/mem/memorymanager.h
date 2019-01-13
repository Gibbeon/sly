#pragma once

#include <map>

#include "sly/global.h"
#include "sly/plugin.h"
#include "sly/mem/heap.h"
#include "sly/mem/mallocheap.h"
#include "sly/mem/builders/memorymanagerbuilder.h"

namespace sly {
    class IMemoryManager : public IPlugin {
    public:
        virtual ~IMemoryManager() {}

        virtual void init(MemoryManagerDesc& desc) = 0;

        virtual vptr_t alloc(size_t ptr) = 0;        
        virtual void free(vptr_t ptr) = 0;

    protected:    
        IMemoryManager() {}
    };  

    class MemoryManager : public IMemoryManager {
    public:
        _GET_TYPE_INFO();
    
        MemoryManager() {}
        virtual ~MemoryManager() {}

        virtual void init(MemoryManagerDesc& desc) {}

        virtual void getHeap(size_t heapId) {}
        virtual void setHeap(size_t heapId, IHeap& heap) {}
        virtual void removeHeap(size_t heapId) {}

        virtual vptr_t alloc(size_t size) { return ::malloc(size); }       
        virtual void free(vptr_t ptr) { ::free(ptr); }

    protected: 
    
    };  
}