#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct ResourceDesc {
        public:
            ptr_t data;
            size_t sizeInBytes;
            size_t stride;
        };

        class IResource  {
        public:
            constexpr static ResourceDesc DEFAULT_DESC = {  }; 
            virtual void write(ptr_t data, size_t size, size_t stride) = 0;
        };

        class ResourceBuilder : public Builder<ResourceDesc> {
        public:
            ResourceBuilder& setSizeInBytes(size_t size) { desc_.sizeInBytes = size; return * this; }
        };
    }
}