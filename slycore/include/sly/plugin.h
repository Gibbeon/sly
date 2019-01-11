#pragma once

#include "sly/runtime/hastypeinfo.h"

namespace sly {
    class IPlugin : public IHasTypeInfo {
    public:
        virtual ~IPlugin() {}

    protected:
        IPlugin() {}
          
    };
}