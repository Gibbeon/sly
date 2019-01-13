#pragma once

#include "sly/runtime/types.h"
#include "sly/runtime/typeinfo.h"

namespace sly {
    class IHasTypeInfo {
    public:
        virtual ~IHasTypeInfo() {}

        virtual const TypeInfo& getType() = 0;

    protected:
        IHasTypeInfo() {}


    };
}

#define _GET_TYPE_INFO()     virtual const TypeInfo& getType() { static const TypeInfo instance = TypeInfo::get<decltype(*this)>(); return instance; }

