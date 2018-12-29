#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    
    struct RenderSystemDesc {
    public:
    };

    class RenderSystemDescBuilder : public Builder<RenderSystemDesc> {
    public:
    };

    class IRenderDevice;
    struct RenderDeviceDesc;
    class IRenderSystem {
    public:
        void CreateRenderDevice(out_ptr_t<IRenderDevice> outDevice, ref_t<RenderDeviceDesc> desc);
    };

}