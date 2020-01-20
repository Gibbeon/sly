#pragma once

#include "sly/runtime/hastypeinfo.h"

namespace sly {
    class IPlugin : public IHasTypeInfo {
    public:
        SLY_TYPEINFO;

        virtual ~IPlugin() {}

        virtual std::string getName() = 0;

    protected:
        IPlugin() {}
          
    };
}