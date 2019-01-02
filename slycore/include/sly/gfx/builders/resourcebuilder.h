#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct ResourceDesc {
        public:
            void* data;
            size_t sizeInBytes;
            size_t stride;
        };

        class ResourceBuilder : public Builder<ResourceDesc> {
        public:
            ResourceBuilder() : Builder() {}        
            virtual ~ResourceBuilder() {}
            
            ResourceBuilder& setSizeInBytes(size_t size) { desc_.sizeInBytes = size; return * this; }
        };
    }
}
