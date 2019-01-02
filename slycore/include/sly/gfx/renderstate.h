#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/renderstatebuilder.h"

namespace sly {
    namespace gfx {
                      
        class IRenderState {
        public:
            virtual ~IRenderState() {}
            virtual void init(RenderStateDesc& desc) = 0;
        protected:
            IRenderState() {}
        };        
    }
}

