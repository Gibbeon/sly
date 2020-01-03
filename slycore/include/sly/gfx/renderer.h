#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/rendererbuilder.h"
#include "sly/gfx/device.h"
#include "sly/ext/plugin.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {

        class IDevice;
        struct Device;
        class IRenderer : public IPlugin {
        public: 
            virtual ~IRenderer() {}
            virtual sly::retval<std::unique_ptr<IDevice>>  createDevice(DeviceDesc& desc) = 0;

        protected:
            IRenderer() {}
        };
    }
}