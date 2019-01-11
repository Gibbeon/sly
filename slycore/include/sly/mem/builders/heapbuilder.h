#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/mem/heaptypes.h"

namespace sly {
    struct HeapDesc {
    public:
        size_t byteSize;
        size_t blockSize;
        eHeapType type;
    };
    
    class HeapBuilder : public Builder<HeapDesc> {
    public:
        HeapBuilder() : Builder() {}
        virtual ~HeapBuilder() {}
    };
}