#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eIndexBufferStripCutValue,
            eIndexBufferStripCutValue_Disabled,
            eIndexBufferStripCutValue_0xFFFF,
            eIndexBufferStripCutValue_0xFFFFFFFF
        );
    }
}