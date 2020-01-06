#pragma once

#include "sly/global.h"
#include "sly/gfx/adapter.h"
#include "sly/gfx/device.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {

        class IDevice;
        class IRenderInterface {
        public: 
            virtual ~IRenderInterface() {}
            
            virtual retval<void> init() = 0;
            virtual retval<void> release() = 0;

            //virtual gsl::span<IRenderAdapter> adapters() const = 0;

            virtual sly::retval<std::unique_ptr<IDevice>>  createDevice(const DeviceDesc& desc = DeviceBuilder().build()) = 0;

        protected:
            IRenderInterface() {}
        };
    }
}