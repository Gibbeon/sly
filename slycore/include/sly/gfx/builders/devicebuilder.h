#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {  
        struct DeviceDesc {
        public:
        };
        
        class DeviceBuilder : public Builder<DeviceDesc> {
        public:
            DeviceBuilder() : Builder() {}
            virtual ~DeviceBuilder() {}
        };

    }
}