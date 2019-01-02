#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        typedef enum  {
            eDataFormat_R32G32B32_FLOAT,
            eDataFormat_R32G32B32A32_FLOAT,
            eDataFormat_R8G8B8A8_UNORM,
            eDataFormat_Max,
            eDataFormat_Default = eDataFormat_R8G8B8A8_UNORM,
        } eDataFormat;     
    }
}