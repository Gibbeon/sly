#pragma once

#include "sly/runtime/types.h"
#include "sly/runtime/typeinfo.h"

namespace sly {

    //create a hash based of a type name


    class IHasTypeInfo {
    public:
        virtual ~IHasTypeInfo() {}

        virtual const TypeInfo& getType() = 0;

    protected:
        IHasTypeInfo() {}


    };
}

