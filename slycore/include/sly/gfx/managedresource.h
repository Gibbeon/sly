#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        class IManagedResource {
        public:         
            virtual ~IManagedResource() {}
            virtual retval<void> release() = 0;

            //virtual IDevice& getDevice();
        protected:
            IManagedResource() {}
        };
    }
}