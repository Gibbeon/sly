#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/rendersystembuilder.h"
#include "sly/gfx/device.h"
#include "sly/plugin.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {

        class IDevice;
        struct Device;
        class IRenderSystem : public IPlugin {
        public: 
            virtual ~IRenderSystem() {}
            virtual sly::retval<std::unique_ptr<IDevice>>  createDevice(DeviceDesc& desc) = 0;

        protected:
            IRenderSystem() {}
        };
    }
}