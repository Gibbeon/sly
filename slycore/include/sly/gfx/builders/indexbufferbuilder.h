#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {
        struct IndexBufferDesc : public ResourceDesc {
        public:
        };
        
        class IndexBufferBuilder : public Builder<IndexBufferDesc> {
        public:
            IndexBufferBuilder() : Builder() {}
            virtual ~IndexBufferBuilder() {}
        };
    }
}

