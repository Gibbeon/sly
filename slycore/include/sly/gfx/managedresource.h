#pragma once

#include "sly/global.h"
#include "sly/gfx/device.h"

namespace sly {
    namespace gfx {
        class IManagedResource {
        public:         
            virtual ~IManagedResource() {}

            //virtual IDevice& getDevice();
        protected:
            IManagedResource() {}
        };
    }
}