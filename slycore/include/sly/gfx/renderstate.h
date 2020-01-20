#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/renderstatebuilder.h"

namespace sly {
    namespace gfx {
                      
        class IRenderState {
        public:
            virtual ~IRenderState() {}
            virtual retval<void> init(const RenderStateDesc& desc) = 0;
            virtual retval<void> release() = 0;
        protected:
            IRenderState() {}
        };        
    }
}

