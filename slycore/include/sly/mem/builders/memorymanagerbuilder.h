#pragma once

#include <vector>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/mem/builders/heapbuilder.h"

namespace sly {
    struct MemorySystemDesc {
    public:
        std::vector<HeapDesc> _heaps;
    };

    class MemorySystemBuilder : public Builder<MemorySystemDesc> {
    public:
        MemorySystemBuilder() : Builder() {}
        virtual ~MemorySystemBuilder() {}
    };
    
}