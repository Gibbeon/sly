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
            virtual void init(ref_t<WindowDesc> desc = IWindow::DEFAULT_DESC) = 0;

            virtual void processMessages() = 0;
            virtual void swapBuffers() = 0;

            virtual void setVisible(bool_t show) = 0;

            virtual ref_t<IRenderTarget>  getBackBuffer() = 0;

/*             virtual size_t getTop() = 0;
            virtual size_t getLeft() = 0;
            virtual size_t getWidth() = 0;
            virtual size_t getHeight() = 0;

            virtual void setTop() = 0;
            virtual void setLeft() = 0;
            virtual void setWidth() = 0;
            virtual void setHeight() = 0; */

            virtual ref_t<ICommandQueue> getDirectCommandQueue() = 0;
        
        //protected:
            constexpr static WindowDesc DEFAULT_DESC = {  };
            friend class WindowBuilder;

        };

        class WindowBuilder : public Builder<WindowDesc> {
        public:
            WindowBuilder() : Builder(IWindow::DEFAULT_DESC) {}
        };
    }
}