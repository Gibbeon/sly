#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eBlendType,
            eBlendType_None,
            eBlendType_Zero,
            eBlendType_One,
            eBlendType_SourceColor,
            eBlendType_InverseSourceColor,
            eBlendType_SourceAlpha,
            eBlendType_InverseSourceAlpha,
            eBlendType_DestinationAlpha,
            eBlendType_InverseDestinationAlpha,
            eBlendType_DestinationColor,
            eBlendType_InverseDestinationColor,
            eBlendType_SourceAlphaSaturation,
            eBlendType_BlendFactor,
            eBlendType_InverseBlendFactor,
            eBlendType_SourceOneColor,
            eBlendType_InverseSourceOneColor,
            eBlendType_SourceOneAlpha,
            eBlendType_InverseSourceOneAlpha
        );
    }
}