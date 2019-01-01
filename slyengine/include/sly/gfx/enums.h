#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        typedef enum  {
            eDataFormat_R32G32B32_FLOAT,
            eDataFormat_R32G32B32A32_FLOAT,
            eDataFormat_R8G8B8A8_UNORM,
            eDataFormat_Default = eDataFormat_R8G8B8A8_UNORM,
            eDataFormat_Max
        } eDataFormat;

        typedef enum  {
            eDataInputClassification_PerVertex,
            eDataInputClassification_PerInstance,
            eDataInputClassification_Default = eDataInputClassification_PerVertex,
            eDataInputClassification_Max
        } eDataInputClassification;   

        typedef enum  {
            ePrimativeType_Triangle,
            ePrimativeType_Default = ePrimativeType_Triangle,
            ePrimativeType_Max
        } ePrimativeType;         
    }
}