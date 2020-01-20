#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {      
        ENUM_DECL(eCompareFunction,
            eCompareFunction_Never,
            eCompareFunction_LessThan,
            eCompareFunction_Equal,
            eCompareFunction_LessOrEqual,
            eCompareFunction_GreaterThan,
            eCompareFunction_NotEqual,
            eCompareFunction_GreaterOrEqual,
            eCompareFunction_Always
        );
    }
}