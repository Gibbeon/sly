#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/shader.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {
                      
        struct RenderStateDesc {
        public:
            RenderStateDesc() :
                vsShader(0), psShader(0),
                sampleMax(UINT_MAX), primitiveType(ePrimativeType_Default),
                numberRenderTargets(1), sampleDesc(1), inputElementCount(0)
            {
                memset(rtvFormats, eDataFormat_Default, 8);
            }

            IShader* vsShader;
            IShader* psShader;
            size_t sampleMax;
            ePrimativeType primitiveType;
            size_t numberRenderTargets;
            size_t sampleDesc;
            eDataFormat rtvFormats[8];
            //List<InputElementDesc> inputElements;
            size_t inputElementCount;
            InputElementDesc inputElements[8];
        };

        class IRenderState {
        public:
            virtual void init(RenderStateDesc& desc) = 0;
        };
        
        class RenderStateBuilder : public Builder<RenderStateDesc> {
        public:
            RenderStateBuilder() : Builder(RenderStateDesc()) {}

            RenderStateBuilder& setVSShader(IShader& shader) { desc_.vsShader = &shader; return * this;}
            RenderStateBuilder& setPSShader(IShader& shader) { desc_.psShader = &shader; return * this;}

            RenderStateBuilder& setSampleMax(size_t max) {desc_.sampleMax = max; return * this;}
            RenderStateBuilder& setPrimitiveType(ePrimativeType type) {desc_.primitiveType = type; return * this;}
            RenderStateBuilder& setNumberRenderTargets(size_t count) {desc_.numberRenderTargets = count; return * this;}
            RenderStateBuilder& setRTVFormats(size_t index, eDataFormat format) { desc_.rtvFormats[index] = format; return * this;}
            RenderStateBuilder& setSampleDesc(size_t desc) {desc_.sampleDesc = desc; return * this;}

            RenderStateBuilder& addInputElementDesriptor(InputElementDesc& desc) { desc_.inputElements[desc_.inputElementCount] = desc; desc_.inputElementCount++;  return * this; }

        };
    }
}

