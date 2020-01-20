#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eBlendLogicOperation,
            eBlendLogicOperation_Clear,
            eBlendLogicOperation_Set,
            eBlendLogicOperation_Copy,
            eBlendLogicOperation_Nothing,
            eBlendLogicOperation_Invert,
            eBlendLogicOperation_And,
            eBlendLogicOperation_NotAnd,
            eBlendLogicOperation_Or,
            eBlendLogicOperation_NotOr,
            eBlendLogicOperation_Xor,
            eBlendLogicOperation_Equal,
            eBlendLogicOperation_AndReverse,
            eBlendLogicOperation_AndInverted,
            eBlendLogicOperation_OrReverse,
            eBlendLogicOperation_OrInverted
        );
    }
}