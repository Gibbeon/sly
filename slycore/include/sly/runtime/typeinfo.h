#pragma once

#include "sly/global.h"
#include "sly/runtime/activator.h"

namespace sly {
    template <class TType = vptr_t>
    struct TypeInfo {
        TypeInfo() :
            name(TOSTRING(TType)),
            id(GET_TYPE_IID(TType)),
            activator(&_activator).
            _activator(GET_TYPE_CTOR())
        {

        }

        std::string name;
        u32 id;   
        IActivator& activator;
    private:
        DefaultAcivator<TType> _activator;  
    };
}