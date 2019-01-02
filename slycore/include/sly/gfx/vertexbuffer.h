#pragma once

#include "sly/global.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/builders/vertexbufferbuilder.h"

namespace sly {
    namespace gfx {
        class IVertexBuffer : public IResource {
        public:
            virtual ~IVertexBuffer() {}
            virtual void init(VertexBufferDesc& desc) = 0;

            virtual size_t getBufferLocation() = 0;
            virtual size_t getSizeInBytes() = 0;
            virtual size_t getStrideInBytes() = 0;
        
        protected:
            IVertexBuffer() {}
        };

    }
}

