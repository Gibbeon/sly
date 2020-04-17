#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/builders/inputelementbuilder.h"
#include "sly/gfx/shader.h"
#include "sly/gfx/rootsignature.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {    

        struct RootDescriptorRangeDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            eDescriptorRangeType rangeType;
            uint_t numDescriptors;
            uint_t baseShaderRegister;
            uint_t registerSpace;
            uint_t offsetInDescriptorsFromTableStart;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(rangeType);
                DESERIALIZE(numDescriptors);
                DESERIALIZE(baseShaderRegister);
                DESERIALIZE(registerSpace);
                DESERIALIZE(offsetInDescriptorsFromTableStart);

                return sly::success();
            }
        };

        struct RootConstantsDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            uint_t shaderRegister;
            uint_t registerSpace;
            uint_t num32BitValues;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(shaderRegister);
                DESERIALIZE(registerSpace);
                DESERIALIZE(num32BitValues);

                return sly::success();
            }
        };
        
        struct RootDescriptorDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            uint_t shaderRegister;
            uint_t registerSpace;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(shaderRegister);
                DESERIALIZE(registerSpace);

                return sly::success();
            }
        };

        struct RootParameterDesc : public ISerializable {  
        public:
            SLY_TYPEINFO;

            eRootParameterType parameterType;
            eShaderVisibility shaderVisibility;
            RootConstantsDesc constants;
            RootDescriptorDesc descriptor;

            std::vector<RootDescriptorRangeDesc> descriptors;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(parameterType);
                DESERIALIZE(shaderVisibility);
                DESERIALIZE(constants);
                DESERIALIZE(descriptor);

                {
                    gfx::RootDescriptorRangeDesc desc;
                    auto& __array = archive.open("descriptors");

                    for(size_t i = 0; i < __array.size(); i++) {                          
                        __array[i].read(desc);
                        descriptors.push_back(desc);
                    }
                    __array.close();
                } 


                return sly::success();
            }
        };

        struct StaticSamplerDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            eFilterType filter;
            eTextureAddressMode addressU;
            eTextureAddressMode addressV;
            eTextureAddressMode addressW;
            real_t mipLODBias;
            uint_t maxAnisotropy;
            eCompareFunction comparisonFunc;
            eStaticBorderColor borderColor;
            real_t minLOD;
            real_t maxLOD;
            uint_t shaderRegister;
            uint_t registerSpace;
            eShaderVisibility shaderVisibility;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(filter, eFiltertype_Anisotropic);
                DESERIALIZE(addressU, eTextureAddressMode_Wrap);
                DESERIALIZE(addressV, eTextureAddressMode_Wrap);
                DESERIALIZE(addressW, eTextureAddressMode_Wrap);
                DESERIALIZE(mipLODBias);
                DESERIALIZE(maxAnisotropy, 16);
                DESERIALIZE(comparisonFunc, eCompareFunction_LessOrEqual);
                DESERIALIZE(borderColor, eStaticBorderColor_Opaque_White);
                DESERIALIZE(minLOD);
                DESERIALIZE(maxLOD, 3.402823466e+38f);
                DESERIALIZE(shaderRegister);
                DESERIALIZE(registerSpace);
                DESERIALIZE(shaderVisibility, eShaderVisibility_All);

                return sly::success();
            }
        };

        struct RootSignatureDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            std::vector<RootParameterDesc> parameters;
            std::vector<StaticSamplerDesc> staticSamplers;
            eRootSignatureFlag flags;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                
                DESERIALIZE(flags);

                {                    
                    auto& __array = archive.open("parameters");

                    for(size_t i = 0; i < __array.size(); i++) {
                        gfx::RootParameterDesc desc;                          
                        __array[i].read(desc);
                        parameters.push_back(desc);
                    }
                    __array.close();
                } 
                {
                    auto& __array = archive.open("staticSamplers");

                    for(size_t i = 0; i < __array.size(); i++) {                          
                        gfx::StaticSamplerDesc desc;                         
                        __array[i].read(desc);
                        staticSamplers.push_back(desc);
                    }
                    __array.close();
                } 

                return sly::success();
            }
        };

        struct BlendTargetDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            bool_t          blendEnable = false;
            bool_t          logicOpEnable = false;
            eBlendType      srcBlend = eBlendType_One;
            eBlendType      destBlend = eBlendType_Zero;
            eBlendOperation blendOp = eBlendOperation_Add;
            eBlendType      srcBlendAlpha = eBlendType_Zero;
            eBlendType      destBlendAlpha = eBlendType_Zero;
            eBlendOperation blendOpAlpha= eBlendOperation_None;
            eBlendLogicOperation logicOp = eBlendLogicOperation_Nothing;
            u8              renderTargetWriteMask = 0xF; // D3D10_COLOR_WRITE_ENABLE_ALL

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                
                DESERIALIZE(blendEnable);
                DESERIALIZE(logicOpEnable);
                DESERIALIZE(srcBlend, eBlendType_One);
                DESERIALIZE(blendOp, eBlendOperation_Add); 
                DESERIALIZE(destBlend, eBlendType_Zero);
                DESERIALIZE(srcBlendAlpha, eBlendType_One);
                DESERIALIZE(destBlendAlpha, eBlendType_Zero); 
                DESERIALIZE(blendOpAlpha, eBlendOperation_Add);
                DESERIALIZE(logicOp, eBlendLogicOperation_Nothing);
                DESERIALIZE(renderTargetWriteMask, 0xF); 

                return sly::success();
            }
        };

        struct BlendStateDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            bool_t alphaToCoverageEnable = false;
            bool_t independentBlendEnable = false;
            uint_t numBlendTargets = 0;

            BlendTargetDesc targets[8];

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                
                DESERIALIZE(alphaToCoverageEnable);
                DESERIALIZE(independentBlendEnable);
                {
                    gfx::BlendTargetDesc desc;
                    auto& __array = archive.open("targets");
                    numBlendTargets = (uint_t)__array.size();
                    Expects(__array.size() <= 8);

                    for(size_t i = 0; i < __array.size(); i++) {                          
                        __array[i].read(targets[i]);
                    }
                    __array.close();
                } 
                

                return sly::success();
            }
        };

        struct StreamOutputDeclarationDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            uint_t stream = 0;
            std::string semanticName;
            uint_t semanticIndex = 0;
            byte_t startComponent = 0;
            byte_t componentCount = 0;
            byte_t outputSlot = 0;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                
                DESERIALIZE(stream);
                DESERIALIZE(semanticName);
                DESERIALIZE(semanticIndex); 
                DESERIALIZE(startComponent);
                DESERIALIZE(componentCount);
                DESERIALIZE(outputSlot); 

                return sly::success();
            }
        };

        struct RenderStateStreamOutput : public ISerializable {
        public:
            SLY_TYPEINFO;

            std::vector<StreamOutputDeclarationDesc> streamOutputDeclaration;
            std::vector<uint_t> bufferStrides;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                
                {
                    gfx::StreamOutputDeclarationDesc desc;
                    auto& __array = archive.open("streamOutputDeclaration");
                    for(size_t i = 0; i < __array.size(); i++) {                          
                        __array[i].read(desc);
                        streamOutputDeclaration.push_back(desc);
                    }
                    __array.close();
                } 
                {
                    uint_t desc;
                    auto& __array = archive.open("bufferStrides");
                    for(size_t i = 0; i < __array.size(); i++) {                          
                        __array[i].read(desc);                        
                        bufferStrides.push_back(desc);
                    }
                    __array.close();
                } 

                return sly::success();
            }
        };

        struct DepthStencilOperationDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            eStencilOperation stencilFailOp = eStencilOperation_Zero;
            eStencilOperation stencilDepthFailOp = eStencilOperation_Zero;
            eStencilOperation stencilPassOp = eStencilOperation_Keep;
            eCompareFunction stencilFunc = eCompareFunction_Never;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                DESERIALIZE(stencilFailOp, eStencilOperation_Zero);
                DESERIALIZE(stencilDepthFailOp, eStencilOperation_Zero);
                DESERIALIZE(stencilPassOp, eStencilOperation_Keep);
                DESERIALIZE(stencilFunc, eCompareFunction_Never);

                return sly::success();
            }
        };

        struct RasterizerStateDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            ePolygonFillMode    fillMode = ePolygonFillMode_Solid;
            ePolygonCullMode    cullMode = ePolygonCullMode_Back;
            bool_t              frontCounterClockwise  = false;
            int_t               depthBias = 0;
            real_t              depthBiasClamp = false;
            real_t              slopeScaledDepthBias = false;
            bool_t              depthClipEnable = false;
            bool_t              multisampleEnable = false;
            bool_t              antialiasedLineEnable = false;
            uint_t              forcedSampleCount = 0;
            bool_t              conservativeRaster = false;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                DESERIALIZE(fillMode, ePolygonFillMode_Solid);
                DESERIALIZE(cullMode, ePolygonCullMode_Back);
                DESERIALIZE(frontCounterClockwise);
                DESERIALIZE(depthBias);
                DESERIALIZE(depthBiasClamp);
                DESERIALIZE(slopeScaledDepthBias);
                DESERIALIZE(multisampleEnable);
                DESERIALIZE(antialiasedLineEnable);
                DESERIALIZE(forcedSampleCount);
                DESERIALIZE(conservativeRaster); 

                return sly::success();
            }
        };

        struct DepthStencilDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            bool_t depthEnable = false;
            eDepthWriteMask depthWriteMask = eDepthWriteMask_All;
            eCompareFunction depthFunc = eCompareFunction_Never;
            bool_t stencilEnable = false;
            uint8_t stencilReadMask = 0x0F;
            uint8_t stencilWriteMask = 0x0F;
            DepthStencilOperationDesc frontFace;
            DepthStencilOperationDesc backFace;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                DESERIALIZE(depthEnable);
                DESERIALIZE(depthWriteMask, eDepthWriteMask_All);
                DESERIALIZE(depthFunc);
                DESERIALIZE(stencilEnable);
                DESERIALIZE(stencilReadMask, 0x0F);
                DESERIALIZE(stencilWriteMask, 0x0F);
                DESERIALIZE(frontFace);
                DESERIALIZE(backFace);

                return sly::success();
            }
        };

        struct SampleDesc : public ISerializable {
        public:
            SLY_TYPEINFO;

            uint_t count = 1;
            uint_t quality = 0;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                 return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(count);
                DESERIALIZE(quality);
                return sly::success();
            }
        
        };

        struct RenderStateDesc : public ISerializable {
        public:
            SLY_TYPEINFO;
            
            // boo
            IShader* vsShader = nullptr;
            IShader* psShader = nullptr;
            IShader* dsShader = nullptr;
            IShader* hsShader = nullptr;
            IShader* gsShader = nullptr; 
            IRootSignature* pRootSignature = nullptr; 
            //IShader* gsShader = nullptr; 

            RootSignatureDesc           signature;

            BlendStateDesc              blend;
            RenderStateStreamOutput     streamOutput;
            RasterizerStateDesc         rasterizerState;
            DepthStencilDesc            depthStencilState;
            eIndexBufferStripCutValue   indexBufferStripCutValue;

            uint_t                      sampleMax;
            ePrimitiveTopologyType      PrimitiveTopologyType;
            SampleDesc                  sampleDesc; // sample desc quality?
            uint_t                      numberRenderTargets;
            eDataFormat                 rtvFormats[8];
            eDataFormat                 dsvFormat;
 
            std::vector<ShaderDesc>         shaders;  
            std::vector<InputElementDesc>   inputElements;          

            UINT                               nodeMask; // used for multi adapter
            //D3D12_CACHED_PIPELINE_STATE        CachedPSO; //blob for caching on adapter
            //D3D12_PIPELINE_STATE_FLAGS         Flags; // used only for WARP 

                    
            sly::retval<void> serialize(sly::ISerializer& archive) {

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE("depthStencilFormat", dsvFormat, eDataFormat_Unknown);
                DESERIALIZE(PrimitiveTopologyType, ePrimitiveTopologyType_Default);
                DESERIALIZE(indexBufferStripCutValue, eIndexBufferStripCutValue_Disabled);
                DESERIALIZE(sampleMax, UINT_MAX);
                DESERIALIZE(signature);
                
                // need to default objects
                DESERIALIZE(blend);
                DESERIALIZE(streamOutput);
                DESERIALIZE("rasterizer", rasterizerState, RasterizerStateDesc());
                DESERIALIZE("depthStencil", depthStencilState, DepthStencilDesc());
                DESERIALIZE(sampleDesc);           

                nodeMask = 0;

                {
                    auto& __array = archive.open("renderTargetFormats");
                    for(size_t i = 0; i < __array.size(); i++) {   
                        __array[i].read(rtvFormats[i], eDataFormat_Default);
                    }
                    
                    numberRenderTargets = (uint_t)std::max((size_t)1, __array.size()); // initialize to a default
                    if(__array.size() < 1) {
                        rtvFormats[0] = eDataFormat_R8G8B8A8_UNORM;
                    }
                    __array.close();
                }                

                {
                    gfx::ShaderDesc shader;
                    auto& __array = archive.open("shaders");
                    for(size_t i = 0; i < __array.size(); i++) {                          
                        __array[i].read(shader);
                        shaders.push_back(shader);
                    }
                    __array.close();
                }  
                {
                    gfx::InputElementDesc element;
                    auto& __array = archive.open("inputElements");
                    for(size_t i = 0; i < __array.size(); i++) {                          
                        __array[i].read(element);
                        inputElements.push_back(element);
                    }
                    __array.close();
                }  

                DESERIALIZE(numberRenderTargets, numberRenderTargets);
                
                return sly::success();
            }
        };

        
        class RenderStateBuilder : public Builder<RenderStateDesc> {
        public:
            RenderStateBuilder() : Builder() {
                _descriptor.vsShader = 0;
                _descriptor.psShader = 0;
                _descriptor.sampleMax = UINT_MAX;
                _descriptor.PrimitiveTopologyType = ePrimitiveTopologyType_Default;
                _descriptor.numberRenderTargets = 1;
                _descriptor.sampleDesc.count = 1;            
                memset(_descriptor.rtvFormats, eDataFormat_Default, 8);
            }

            virtual ~RenderStateBuilder() {}

            RenderStateBuilder& setVSShader(IShader& shader) { _descriptor.vsShader = &shader; return * this;}
            RenderStateBuilder& setPSShader(IShader& shader) { _descriptor.psShader = &shader; return * this;}

            RenderStateBuilder& setSampleMax(uint_t max) {_descriptor.sampleMax = max; return * this;}
            RenderStateBuilder& setPrimitiveType(ePrimitiveTopologyType type) {_descriptor.PrimitiveTopologyType = type; return * this;}
            RenderStateBuilder& setNumberRenderTargets(uint_t count) {_descriptor.numberRenderTargets = count; return * this;}
            RenderStateBuilder& setRTVFormats(uint_t index, eDataFormat format) { _descriptor.rtvFormats[index] = format; return * this;}
            RenderStateBuilder& setSampleDesc(uint_t desc) {_descriptor.sampleDesc.count  = desc; return * this;}

            RenderStateBuilder& addInputElementDesriptor(const InputElementDesc& desc) { _descriptor.inputElements.push_back(desc); return * this; }

        };
    }
}

