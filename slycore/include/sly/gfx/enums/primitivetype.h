#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(ePrimativeType, 
            ePrimativeType_Triangle,
            ePrimativeType_Max,
            ePrimativeType_Default = ePrimativeType_Triangle
        );         
    }
}