#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    struct PluginManagerDesc {
    public:
    
    };

    class PluginManagerBuilder : public Builder<PluginManagerDesc> {
    public:
        PluginManagerBuilder() : Builder() {}
        virtual ~PluginManagerBuilder() {}
    };
}