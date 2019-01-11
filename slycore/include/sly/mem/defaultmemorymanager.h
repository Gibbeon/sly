#pragma once

#include <map>

#include "sly/global.h"
#include "sly/mem/memorymanager.h"

namespace sly {

    class DefaultMemoryManager : public IMemoryManager {
    public:
        virtual ~DefaultMemoryManager() {}

        virtual void init(MemoryManagerDesc& desc);

        virtual IHeap& getGlobalHeap();
        virtual void setGlobalHeap(IHeap& hHandle);

        virtual void getHeap(size_t heapId);
        virtual void setHeap(size_t heapId, IHeap& heap);
        virtual void removeHeap(size_t heapId);

        virtual void alloc(vptr_t ptr);        
        virtual void free(vptr_t ptr);

    protected:    
        DefaultMemoryManager() {}

        IHeap* _default;
        size_t _nextHeapId;
        std::map<size_t, IHeap&> _heaps;
    };          
}