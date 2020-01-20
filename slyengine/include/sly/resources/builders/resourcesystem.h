#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly { 

    struct ResourceSystemDesc {
    public:
    };

    class ResourceSystemBuilder : public Builder<ResourceSystemDesc> {
    public:
        ResourceSystemBuilder() : Builder() {}
        virtual ~ResourceSystemBuilder() {}            
    };   
}



