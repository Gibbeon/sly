#pragma once

#include "sly/global.h"
#include "sly/gfx/managedresource.h"
#include "sly/gfx/viewport.h"
#include "sly/gfx/color.h"
#include "sly/math/primatives.h"
#include "sly/gfx/builders/commandlistbuilder.h"

namespace sly {
    namespace gfx {
        class IRenderState;
        class IVertexBuffer;
        class IRenderTarget; 
        class ICommandList : public IManagedResource {
        public:
            virtual ~ICommandList() {} 
            virtual retval<void> init(const CommandListDesc& desc = CommandListBuilder().build()) =0;
            virtual retval<void> release() = 0;

            virtual void begin() = 0;
            virtual void end() = 0;

            virtual void setRenderState(IRenderState& state) = 0;
            virtual void setViewport(Viewport& viewport) = 0;
            virtual void setScissorRect(rect_t<real_t> rect) = 0;
            virtual void setVertexBuffer(IVertexBuffer& buffer) = 0;
            virtual void setRenderTarget(IRenderTarget& target) = 0;
            
            virtual void clear(color_t color) = 0;

            virtual void draw(size_t, size_t, size_t, size_t) = 0;    
        protected:
            ICommandList() {}  
        };
    }
}

