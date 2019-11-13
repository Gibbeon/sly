#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eDataInputClassification, 
            eDataInputClassification_PerVertex,
            eDataInputClassification_PerInstance,
            eDataInputClassification_Max,
            eDataInputClassification_Default = eDataInputClassification_PerVertex
        );          
    }
}