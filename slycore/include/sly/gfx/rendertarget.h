#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/rendertargetbuilder.h"

namespace sly {
    namespace gfx {
        class IRenderTarget : public IResource {
        public:
            virtual ~IRenderTarget() {}
        
        protected:
            IRenderTarget() {}
        };
    }
}

