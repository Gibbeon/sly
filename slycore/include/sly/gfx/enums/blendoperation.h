#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eBlendOperation,
            eBlendOperation_None,
            eBlendOperation_Add,
            eBlendOperation_Subtract,
            eBlendOperation_ReverseSubtract,
            eBlendOperation_Min,
            eBlendOperation_Max
        );
    }
}