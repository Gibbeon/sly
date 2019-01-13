#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/device.h"
#include "sly/plugin.h"

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
        struct Device;
        class IRenderSystem : public IPlugin {
        public:
            virtual ~IRenderSystem() {}
            virtual void createDevice(IDevice** outDevice, DeviceDesc& desc) = 0;

        protected:
            IRenderSystem() {}
        };
    }
}