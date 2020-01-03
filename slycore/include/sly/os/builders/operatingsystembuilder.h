#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
        
    namespace os {

        struct OperatingSystemDesc 
        {
            
        };

        class OperatingSystemBuilder : public sly::Builder<OperatingSystemDesc>
        {
        public:
            OperatingSystemBuilder() : Builder() {}
            virtual ~OperatingSystemBuilder() {}
        };
    }
}