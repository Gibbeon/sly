#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct RenderSystemDesc {
        public:
        };

        class RenderSystemBuilder : public Builder<RenderSystemDesc> {
        public:
            RenderSystemBuilder() : Builder({}) {}
        };

        class IDevice;
        struct DeviceDesc;
        class IRenderSystem {
        public:
            virtual void createDevice(out_ptr_t<IDevice> outDevice, ref_t<DeviceDesc> desc) = 0;

        protected:
            constexpr static RenderSystemDesc DEFAULT = {  }; 
        };
    }
}