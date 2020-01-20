#pragma once

#include <vector>

#include "sly/global.h"
#include "sly/kernel.h"
#include "sly/gfx/renderinterface.h"
#include "sly/gfx/builders/graphicsystembuilder.h"

// this is actually a plugin, ignoring for now

namespace sly {
    
    class Kernel;
    namespace gfx {
        class IRenderInterface;
        
        class IRenderSystem {
        public:
            virtual ~IRenderSystem() {}
            
            virtual retval<void> init() = 0;
            virtual retval<void> release() = 0;

            virtual std::vector<IRenderInterface*>& interfaces() = 0;
        
        protected:
            IRenderSystem() {}
        };

        class RenderSystem : public IRenderSystem {
        public:
            RenderSystem(sly::Kernel& kernel);
            virtual ~RenderSystem();

            virtual retval<void> init();
            virtual retval<void> release();
          
            virtual std::vector<IRenderInterface*>& interfaces();
        
        protected:
            sly::Kernel& _kernel;
            std::vector<IRenderInterface*> _interfaces;        
        };
    }
}