#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/shader.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {
                      
        struct RenderStateDesc {
        public:
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

        
        class RenderStateBuilder : public Builder<RenderStateDesc> {
        public:
            RenderStateBuilder() : Builder() {
                _descriptor.vsShader = 0;
                _descriptor.psShader = 0;
                _descriptor.sampleMax = UINT_MAX;
                _descriptor.primitiveType = ePrimativeType_Default;
                _descriptor.numberRenderTargets = 1;
                _descriptor.sampleDesc = 1;
                _descriptor.inputElementCount = 0;                
                memset(_descriptor.rtvFormats, eDataFormat_Default, 8);
            }

            virtual ~RenderStateBuilder() {}

            RenderStateBuilder& setVSShader(IShader& shader) { _descriptor.vsShader = &shader; return * this;}
            RenderStateBuilder& setPSShader(IShader& shader) { _descriptor.psShader = &shader; return * this;}

            RenderStateBuilder& setSampleMax(size_t max) {_descriptor.sampleMax = max; return * this;}
            RenderStateBuilder& setPrimitiveType(ePrimativeType type) {_descriptor.primitiveType = type; return * this;}
            RenderStateBuilder& setNumberRenderTargets(size_t count) {_descriptor.numberRenderTargets = count; return * this;}
            RenderStateBuilder& setRTVFormats(size_t index, eDataFormat format) { _descriptor.rtvFormats[index] = format; return * this;}
            RenderStateBuilder& setSampleDesc(size_t desc) {_descriptor.sampleDesc = desc; return * this;}

            RenderStateBuilder& addInputElementDesriptor(const InputElementDesc& desc) { _descriptor.inputElements[_descriptor.inputElementCount] = desc; _descriptor.inputElementCount++;  return * this; }

        };
    }
}

