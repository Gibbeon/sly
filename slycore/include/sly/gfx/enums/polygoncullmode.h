#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(ePolygonCullMode,
            ePolygonCullMode_None,
            ePolygonCullMode_Front,
            ePolygonCullMode_Back
        );
    }
}