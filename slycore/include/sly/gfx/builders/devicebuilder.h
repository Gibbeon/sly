#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {  
        struct DeviceDesc {
        public:
            u32 adapter;
        };
        
        class DeviceBuilder : public Builder<DeviceDesc> {
        public:
            DeviceBuilder() : Builder() {
                _descriptor.adapter = -1;                            
            }
            
            virtual ~DeviceBuilder() {}
        };

    }
}