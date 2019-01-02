#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        typedef enum  {
            ePrimativeType_Triangle,
            ePrimativeType_Max,
            ePrimativeType_Default = ePrimativeType_Triangle
        } ePrimativeType;         
    }
}