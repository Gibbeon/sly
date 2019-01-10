#pragma once

#include "sly/global.h"
#include "sly/builder.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {
        struct RenderSystemDesc {
        public:
        };

        class RenderSystemBuilder : public Builder<RenderSystemDesc> {
        public:
            RenderSystemBuilder() : Builder() {}
        };

        class IDevice;
        struct DeviceDesc;
        class IRenderSystem {
        public:
            virtual ~IRenderSystem() {}
            virtual void createDevice(IDevice** outDevice, DeviceDesc& desc) = 0;

        protected:
            IRenderSystem() {}
        };
    }
}