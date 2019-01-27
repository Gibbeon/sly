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

#define _GET_TYPE_INFO()     virtual const sly::TypeInfo& getType() { static const sly::TypeInfo instance = sly::TypeInfo::get<std::remove_reference<decltype(*this)>::type>(); return instance; }

