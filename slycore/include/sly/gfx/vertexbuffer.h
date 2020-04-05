#pragma once

#include "sly/global.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/builders/vertexbufferbuilder.h"

namespace sly {
    namespace gfx {
        class IVertexBuffer : public virtual IResource {
        public:
            virtual ~IVertexBuffer() {}
            virtual retval<void> init(const BufferDesc& desc) = 0;

            virtual size_t address() = 0;
            virtual size_t size() = 0;
            virtual size_t stride() = 0;
        
        protected:
            IVertexBuffer() {}
        };
    }
}

