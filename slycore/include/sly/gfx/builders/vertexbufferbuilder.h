#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/inputelement.h"

namespace sly {
    namespace gfx {
        struct VertexBufferDesc : public ResourceDesc {
        public:
            VertexBufferDesc() : count(0), ResourceDesc() {}
            
            size_t count;
        };


        class VertexBufferBuilder : public Builder<VertexBufferDesc> {
        public:
            VertexBufferBuilder() : Builder() {}            
            virtual ~VertexBufferBuilder() {}

            VertexBufferBuilder& setData(vptr_t data, size_t count, size_t stride) { desc_.data = data; desc_.count = count; desc_.stride = stride;  desc_.sizeInBytes = count * stride; return * this; }
        };
    }
}

