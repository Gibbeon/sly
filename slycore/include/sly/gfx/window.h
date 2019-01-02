#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/windowbuilder.h"

namespace sly {
    namespace gfx {
        class ICommandQueue;
        class IWindow {
        public:
            virtual ~IWindow() {}
            virtual void init(WindowDesc& desc) = 0;

            virtual void processMessages() = 0;
            virtual void swapBuffers() = 0;

            virtual void setVisible(bool_t show) = 0;

            virtual IRenderTarget&  getBackBuffer() = 0;
            virtual ICommandQueue& getDirectCommandQueue() = 0;

        protected:
            IWindow() {}
        };
    }
}