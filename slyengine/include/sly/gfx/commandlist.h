#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/viewport.h"
#include "sly/gfx/color.h"
#include "sly/math/rect.h"

namespace sly {
    namespace gfx {
        struct CommandListDesc {
        public:
        };

        class IRenderState;
        class IVertexBuffer;
        class IRenderTarget; 
        class ICommandList {
        public:
            virtual void begin() = 0;
            virtual void end() = 0;

            virtual void setRenderState(ref_t<IRenderState> state) = 0;
            virtual void setViewport(ref_t<Viewport> viewport) = 0;
            virtual void setScissorRect(rect_t<long> rect) = 0;
            virtual void setVertexBuffer(ref_t<IVertexBuffer> buffer) = 0;
            virtual void setRenderTarget(ref_t<IRenderTarget> target) = 0;
            
            virtual void clear(color_t<> color) = 0;

            virtual void draw(size_t, size_t, size_t, size_t) = 0;

            //virtual void setViewport() = 0;
            //virtual void setCamera() = 0;
            //virtual void setProjection() = 0;
            //virtual void setScissorRect() = 0;
            //virtual void setVSShader() = 0;
            //virtual void setPSShader() = 0;
            //virtual void setVertexBuffer() = 0;
            //virtual void setIndexBuffer() = 0;
            //virtual void setTexture() = 0;
            //virtual void drawIndexed() = 0;

        protected:
            constexpr static CommandListDesc DEFAULT_DESC = {  };
            friend class CommandListBuilder;           
        };
        
        class CommandListBuilder : public Builder<CommandListDesc> {
        public:
            CommandListBuilder() : Builder(ICommandList::DEFAULT_DESC) {}
        };
    }
}