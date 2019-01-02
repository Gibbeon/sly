#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        typedef enum  {
            eDataInputClassification_PerVertex,
            eDataInputClassification_PerInstance,
            eDataInputClassification_Max,
            eDataInputClassification_Default = eDataInputClassification_PerVertex,
        } eDataInputClassification;          
    }
}