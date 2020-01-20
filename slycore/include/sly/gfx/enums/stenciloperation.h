#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eStencilOperation,
            eStencilOperation_Keep,
            eStencilOperation_Zero,
            eStencilOperation_Replace,
            eStencilOperation_IncrementClamp,
            eStencilOperation_DecrementClamp,
            eStencilOperation_Invert,
            eStencilOperation_IncrementWrap,
            eStencilOperation_DecrementWrap
        );
    }
}