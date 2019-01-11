#pragma once

#include <string>

#include "sly/runtime/activator.h"

#define _CLASS_NAME_(x) STRINGIFY(x)
#define _IID_(x) IID_ ## x
#define _TYPE_INFO_(typeName) virtual TypeInfo getTypeInfo() { return TypeInfo(_CLASS_NAME_(typeName), _IID_(typeName)); }

namespace sly {
    struct TypeInfo {
        TypeInfo(std::string typeName, u32 typeId) :
            name(typeName),
            id(typeId)
        {
        }

        std::string name;
        u32 id;  
    private:
    };
}