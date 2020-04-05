#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/shader.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {       

        struct BlendTargetDesc {
            bool_t          BlendEnable;
            bool_t          LogicOpEnable;
            eBlendType      SrcBlend;
            eBlendType      DestBlend;
            eBlendOperation BlendOp;
            eBlendType      SrcBlendAlpha;
            eBlendType      DestBlendAlpha;
            eBlendOperation BlendOpAlpha;
            eBlendLogicOperation LogicOp;
            u8              RenderTargetWriteMask;
        };

        struct BlendStateDesc {
        public:        
            bool_t AlphaToCoverageEnable;
            bool_t IndependentBlendEnable;
            BlendTargetDesc targets[8];
        };

        struct StreamOutputDeclarationDesc {
        public:
            uint_t Stream;
            std::string SemanticName;
            uint_t SemanticIndex;
            byte_t StartComponent;
            byte_t ComponentCount;
            byte_t OutputSlot;
        };

        struct RenderStateStreamOutput {
            std::vector<StreamOutputDeclarationDesc> streamOutputDeclaration;
            std::vector<uint_t> bufferStrides;
        };

        struct DepthStencilOperationDesc
        {
            eStencilOperation StencilFailOp;
            eStencilOperation StencilDepthFailOp;
            eStencilOperation StencilPassOp;
            eCompareFunction StencilFunc;
        };

        struct RasterizerStateDesc {
            ePolygonFillMode    FillMode;
            ePolygonCullMode    CullMode;
            bool_t              FrontCounterClockwise;
            int_t               DepthBias;
            real_t              DepthBiasClamp;
            real_t              SlopeScaledDepthBias;
            bool_t              DepthClipEnable;
            bool_t              MultisampleEnable;
            bool_t              AntialiasedLineEnable;
            uint_t              ForcedSampleCount;
            bool_t              ConservativeRaster;
        };

        struct DepthStencilDesc
        {
            bool_t DepthEnable;
            eDepthWriteMask DepthWriteMask;
            eCompareFunction DepthFunc;
            bool_t StencilEnable;
            uint8_t StencilReadMask;
            uint8_t StencilWriteMask;
            DepthStencilOperationDesc FrontFace;
            DepthStencilOperationDesc BackFace;
        };

        

        struct RenderStateDesc : public virtual ISerializable {
        public:
            SLY_TYPEINFO;
            
            IShader* vsShader;
            IShader* psShader;
            IShader* dsShader;
            IShader* hsShader;
            IShader* gsShader; 

            BlendStateDesc              blend;
            RenderStateStreamOutput     streamOutput;
            RasterizerStateDesc         rasterizerState;
            DepthStencilDesc            depthStencilState;
            eIndexBufferStripCutValue   indexBufferStripCutValue;

            size_t                      sampleMax;
            ePrimativeType              primitiveType;
            size_t                      sampleDesc;
            size_t                      numberRenderTargets;
            eDataFormat                 rtvFormats[8];
            eDataFormat                 dsvFormat;

            std::vector<InputElementDesc>   inputElements; 
            std::vector<ShaderDesc>         shaders;            

            //UINT                               NodeMask; // used for multi adapter
            //D3D12_CACHED_PIPELINE_STATE        CachedPSO; //blob for caching on adapter
            //D3D12_PIPELINE_STATE_FLAGS         Flags; // used only for WARP 

                    
            sly::retval<void> serialize(sly::ISerializer& archive) {

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                std::string type_string;
                archive.read("primitiveType", type_string);
                ePrimativeType bob;

                primitiveType = sly::Enum<ePrimativeType>::parse(type_string.c_str());
                auto shaderArray = archive.array("shaders");

                for(size_t i = 0; i < shaderArray->size(); i++) {
                    gfx::ShaderDesc shader;
                    shaderArray->read(i, shader);
                    shaders.push_back(shader);
                }

                auto elementsArray = archive.array("inputElements");

                for(size_t i = 0; i < elementsArray->size(); i++) {
                    gfx::InputElementDesc element;
                    elementsArray->read(i, element);
                    inputElements.push_back(element);
                }
                
                return sly::success();
            }
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

            RenderStateBuilder& addInputElementDesriptor(const InputElementDesc& desc) { _descriptor.inputElements.push_back(desc); return * this; }

        };
    }
}

