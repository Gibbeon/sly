#pragma once

#include "sly/runtime/types.h"
#include "sly/runtime/typeinfo.h"

namespace sly {

    class IHasTypeInfo {
    public:
        virtual ~IHasTypeInfo() {}

        virtual TypeInfo getTypeInfo() = 0;

    protected:
        IHasTypeInfo() {}
    };
}

