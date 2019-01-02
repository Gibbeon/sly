#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct WindowDesc {
        public:
        };

        class ICommandQueue;
        class IWindow {
        public:
            virtual void init(WindowDesc& desc) = 0;

            virtual void processMessages() = 0;
            virtual void swapBuffers() = 0;

            virtual void setVisible(bool_t show) = 0;

            virtual IRenderTarget&  getBackBuffer() = 0;

/*             virtual size_t getTop() = 0;
            virtual size_t getLeft() = 0;
            virtual size_t getWidth() = 0;
            virtual size_t getHeight() = 0;

            virtual void setTop() = 0;
            virtual void setLeft() = 0;
            virtual void setWidth() = 0;
            virtual void setHeight() = 0; */

            virtual ICommandQueue& getDirectCommandQueue() = 0;
        
        };

        class WindowBuilder : public Builder<WindowDesc> {
        public:
            WindowBuilder() : Builder({}) {}
        };
    }
}