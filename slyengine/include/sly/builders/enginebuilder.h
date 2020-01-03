#pragma once

#include "sly/global.h"
#include "sly/builder.h"


namespace sly { 
    struct EngineDesc {
    public:
    };

    class EngineBuilder : public Builder<EngineDesc> {
    public:
        EngineBuilder() : Builder() {}
        virtual ~EngineBuilder() {}
            
    };   
}



