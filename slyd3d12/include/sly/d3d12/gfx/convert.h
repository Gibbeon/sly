#pragma once

#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        class D3D12Convert {
        public:
            static DXGI_FORMAT convert(eDataFormat value) {
                size_t lookup[eDataFormat_Max];
                lookup[eDataFormat_R32G32B32_FLOAT] = DXGI_FORMAT_R32G32B32_FLOAT;                
                lookup[eDataFormat_R32G32B32A32_FLOAT] = DXGI_FORMAT_R32G32B32A32_FLOAT;                
                lookup[eDataFormat_R8G8B8A8_UNORM] = DXGI_FORMAT_R8G8B8A8_UNORM;

                return (DXGI_FORMAT)lookup[value];
            }
        };

        struct D3D12_VIEWPORT_CAST : public D3D12_VIEWPORT {
            D3D12_VIEWPORT_CAST(Viewport& src) {
                this->Height = src.height;
                this->Width = src.width;
                this->TopLeftX = src.x;
                this->TopLeftY = src.y;
                this->MinDepth = src.maxDepth;
                this->MaxDepth = src.minDepth;
            }
        };

        struct D3D12_RECT_CAST : public D3D12_RECT {
            D3D12_RECT_CAST(rect_t src) {
                this->left = (LONG)src.left;
                this->top = (LONG)src.top;
                this->right = (LONG)src.right;
                this->bottom = (LONG)src.bottom;
            }
        };

        struct D3D12_INPUT_ELEMENT_DESC_CAST : public D3D12_INPUT_ELEMENT_DESC {
            D3D12_INPUT_ELEMENT_DESC_CAST(InputElementDesc& src) {
                this->SemanticName = src.semanticName;
                this->SemanticIndex = 0;
                this->InstanceDataStepRate = 0;
                this->InputSlot = 0;
                this->AlignedByteOffset = (UINT)src.offset;
                this->InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
                this->Format = D3D12Convert::convert(src.format);
            }
        };
        
    }
}

