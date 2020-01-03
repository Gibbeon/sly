#pragma once

#include <vector>

#include "sly/global.h"
#include "sly/gfx/renderer.h"
#include "sly/gfx/builders/graphicsystembuilder.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {
        class IGraphicSystem {
        public:
            virtual ~IGraphicSystem() {}
            
            virtual retval<void> init(GraphicSystemDesc&) = 0;
            virtual gsl::span<const IRenderer* const>  renderers() = 0;
        
        protected:
            IGraphicSystem() {}
        };

        class GraphicSystem : public IGraphicSystem {
        public:
            GraphicSystem() {}
            virtual ~GraphicSystem() {}

            virtual retval<void> init(GraphicSystemDesc&) { return success(); }
            virtual gsl::span<const IRenderer* const> renderers() { return _availableRenderers; }

            static retval<void> addRenderer(IRenderer* system) {
                _availableRenderers.push_back(system);
                return success();
            }
        
        protected:
            static std::vector<IRenderer*>          _availableRenderers;        
        };
    }
}