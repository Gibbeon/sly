#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/rendertarget.h"

namespace sly {
    namespace gfx {
        struct TextureDesc {
        public:
        };

        class TextureBuilder : public Builder<TextureDesc> {
        public:
        };

        class ITexture : public IRenderTarget {
        public:
        
        protected:
            using IRenderTarget::IRenderTarget;
        
            constexpr static TextureDesc DEFAULT = {  }; 
        };
    }
}

