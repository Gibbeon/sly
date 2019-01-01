#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {
        struct IndexBufferDesc : public ResourceDesc {
        public:
        };

        class IIndexBuffer : public IResource {
        public:
        
        protected:
            using IResource::IResource;

        protected:
            constexpr static IndexBufferDesc DEFAULT_DESC = {  }; 
            friend class IndexBufferBuilder;
        };

        
        class IndexBufferBuilder : public Builder<IndexBufferDesc> {
        public:
            IndexBufferBuilder() : Builder(IIndexBuffer::DEFAULT_DESC) {}
        };
    }
}

