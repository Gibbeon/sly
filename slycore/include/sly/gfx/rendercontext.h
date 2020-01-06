#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/rendercontextbuilder.h"

namespace sly {
    namespace gfx {
        class ICommandQueue;
        class IRenderContext {
        public:
            virtual ~IRenderContext() {}
            virtual retval<void> init(const RenderContextDesc& desc) = 0;
            virtual retval<void> release() = 0;

            virtual void processMessages() = 0;
            virtual void present() = 0;

            virtual void setVisible(bool_t show) = 0;

            virtual IRenderTarget& getDrawBuffer() = 0;
            virtual ICommandQueue& getDirectCommandQueue() = 0;

        protected:
            IRenderContext() {}
        };
    }
}