#pragma once

#include <vector>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/mem/builders/heapbuilder.h"

namespace sly {
    struct MemoryManagerDesc {
    public:
        std::vector<HeapDesc> _heaps;
    };

    class MemoryManagerBuilder : public Builder<MemoryManagerDesc> {
    public:
        MemoryManagerBuilder() : Builder() {}
        virtual ~MemoryManagerBuilder() {}
    };
    
}