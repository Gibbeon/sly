#pragma once

#include "sly/global.h"
#include "sly/gfx/rendertarget.h"
#include "sly/gfx/builders/texturebuilder.h"

namespace sly {
    namespace gfx {
        class ITexture : public IRenderTarget {
        public:
            virtual ~ITexture() {}
            virtual void init(TextureDesc& desc) = 0;
            
        protected:
            ITexture() {}
        };
    }
}

