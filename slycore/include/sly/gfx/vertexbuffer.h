#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/inputelement.h"

namespace sly {
    namespace gfx {
        struct VertexBufferDesc : public ResourceDesc {
        public:
            VertexBufferDesc() : count(0), ResourceDesc(IResource::DEFAULT_DESC) {}
            
            size_t count;
        };

        class IVertexBuffer : public IResource {
        public:
            virtual void init(VertexBufferDesc& desc) = 0;

            virtual size_t getBufferLocation() = 0;
            virtual size_t getSizeInBytes() = 0;
            virtual size_t getStrideInBytes() = 0;
        
        protected:
            using IResource::IResource;
        
            friend class VertexBufferBuilder;
        };

        class VertexBufferBuilder : public Builder<VertexBufferDesc> {
        public:
            VertexBufferBuilder() : Builder(VertexBufferDesc()) {}

            VertexBufferBuilder& setData(void* data, size_t count, size_t stride) { desc_.data = data; desc_.count = count; desc_.stride = stride;  desc_.sizeInBytes = count * stride; return * this; }
        };
    }
}

