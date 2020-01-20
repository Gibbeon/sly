#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
        
    namespace os {

        struct SystemInterfaceDesc 
        {
            
        };

        class SystemInterfaceBuilder : public sly::Builder<SystemInterfaceDesc>
        {
        public:
            SystemInterfaceBuilder() : Builder() {}
            virtual ~SystemInterfaceBuilder() {}
        };
    }
}