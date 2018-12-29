#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {

    struct RenderWindowDesc {
    public:
    };

    class RenderWindowDescBuilder : public Builder<RenderWindowDesc> {
    public:
    };
    
    class IRenderCommandQueue;
    class IRenderWindow {
    public:
        void ProcessEvents();
        void SwapBuffers();
        ref_t<IRenderCommandQueue> GetRenderQueue();
    };
}