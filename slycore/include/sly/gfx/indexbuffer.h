#pragma once

#include "sly/global.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/builders/indexbufferbuilder.h"

namespace sly {
    namespace gfx {
        class IIndexBuffer : public IResource {
        public:
            virtual ~IIndexBuffer() {}            
            virtual void init(IndexBufferDesc& desc) = 0;
        
        protected:
            IIndexBuffer() {}
        };
    }
}

