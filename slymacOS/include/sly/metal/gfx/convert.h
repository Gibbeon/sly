#pragma once

#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        /*class METALConvert {
        public:
            static DXGI_FORMAT convert(eDataFormat value) {
                size_t lookup[eDataFormat_Max];
                lookup[eDataFormat_R32G32B32_FLOAT] = DXGI_FORMAT_R32G32B32_FLOAT;                
                lookup[eDataFormat_R32G32B32A32_FLOAT] = DXGI_FORMAT_R32G32B32A32_FLOAT;                
                lookup[eDataFormat_R8G8B8A8_UNORM] = DXGI_FORMAT_R8G8B8A8_UNORM;

                return (DXGI_FORMAT)lookup[value];
            }
        };

        struct METAL_VIEWPORT_CAST : public METAL_VIEWPORT {
            METAL_VIEWPORT_CAST(Viewport& src) {
                this->Height = src.height;
                this->Width = src.width;
                this->TopLeftX = src.x;
                this->TopLeftY = src.y;
                this->MinDepth = src.maxDepth;
                this->MaxDepth = src.minDepth;
            }
        };

        struct METAL_RECT_CAST : public METAL_RECT {
            METAL_RECT_CAST(rect_t src) {
                this->left = (LONG)src.left;
                this->top = (LONG)src.top;
                this->right = (LONG)src.right;
                this->bottom = (LONG)src.bottom;
            }
        };

        struct METAL_INPUT_ELEMENT_DESC_CAST : public METAL_INPUT_ELEMENT_DESC {
            METAL_INPUT_ELEMENT_DESC_CAST(InputElementDesc& src) {
                this->SemanticName = src.semanticName;
                this->SemanticIndex = 0;
                this->InstanceDataStepRate = 0;
                this->InputSlot = 0;
                this->AlignedByteOffset = (UINT)src.offset;
                this->InputSlotClass = METAL_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
                this->Format = METALConvert::convert(src.format);
            }
        };*/
        
    }
}

