#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/drawablefragment.h"

namespace sly {

    struct DrawableDesc : public sly::ISerializable {
    public:
        SLY_TYPEINFO;

        std::vector<gfx::BufferDesc> buffers;
        gfx::RenderStateDesc state;
        
        sly::retval<void> serialize(sly::ISerializer& archive) {
            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {
            auto& bufferArray = archive.property("buffers");

            for(size_t i = 0; i < bufferArray.size(); i++) {
                gfx::BufferDesc buffer;
                bufferArray.at(i).read(buffer);
                buffers.push_back(buffer);
            }
            bufferArray.close();
            
            archive.property("state").read(state);

            return sly::success();
        }
    };

    class Drawable {
    public:
        Drawable(gfx::IDevice& device): _device(device), _indexBuffer(nullptr) {

        }

        ~Drawable() {

        }

        retval<void>init(DrawableDesc& desc) {
            for(auto& buffer: desc.buffers) {
                switch(buffer.bufferType) {
                    case gfx::eBufferType_Vertex:
                        auto vb = _device.createVertexBuffer(buffer);
                        //vb->init(buffer);
                        _vertexBuffers.push_back(vb);
                    break;
                }
            }

            DrawableFragmentDesc fragmentDesc;

            fragmentDesc.baseVertexLocation = 0;
            fragmentDesc.countPerInstance = 3;
            fragmentDesc.instanceCount = 1;
            fragmentDesc.startInstanceLocation = 0;
            fragmentDesc.startLocation = 0;

            DrawableFragment fragment;
            fragment.init(fragmentDesc);
            _fragments.push_back(fragment);

            /*auto rsState = device->createRenderState( 
                sly::gfx::RenderStateBuilder()
                    .setVSShader(vsshader) //renderPipelineDesc.SetVertexFunction(vertFunc);
                    .setPSShader(psshader) //renderPipelineDesc.SetFragmentFunction(fragFunc);
                    .setPrimitiveType(sly::gfx::ePrimativeType_Triangle)
                    .setRTVFormats(0, sly::gfx::eDataFormat_R8G8B8A8_UNORM) //renderPipelineDesc.GetColorAttachments()[0].SetPixelFormat(mtlpp::PixelFormat::BGRA8Unorm);
                    .addInputElementDesriptor(            
                        sly::gfx::InputElementBuilder()
                            .setSemanticName("POSITION")
                            .setFormat(sly::gfx::eDataFormat_R32G32B32_FLOAT)
                            .build()
                    )
                    .addInputElementDesriptor(
                        sly::gfx::InputElementBuilder()
                            .setSemanticName("COLOR")
                            .setFormat(sly::gfx::eDataFormat_R32G32B32A32_FLOAT)
                            .setOffset(12)
                            .build()
                    )
                    .build();*/
                //);

                //gotta have the shaders

            for(auto& shader: desc.state.shaders) {
                auto pShader = _device.createShader(shader);
                switch(shader.shaderType) {
                    case gfx::eShaderType_Vertex:
                        desc.state.vsShader = pShader;
                    case gfx::eShaderType_Pixel:
                        desc.state.psShader = pShader;
                    break;
                }

                // make unique is trying to destroy the shader here
            }

            _state = _device.createRenderState(desc.state);            
            return success();      

        }

        retval<void> draw(  gfx::ICommandList& list
                            , uint_t vertexSlot = 0) const {

            list.setRenderState(*_state);
            list.setVertexBuffer(*_vertexBuffers[0]);

            //IF_EXISTS(_indexBuffer, list.setIndexBuffer(_indexBuffer));

            if(_indexBuffer == nullptr) {
                for(auto& fragment : _fragments) {
                    fragment.drawNonIndexed(list);
                }
            } else {
                for(auto& fragment : _fragments) {
                    fragment.drawIndexed(list);
                }
            }

            return success();   
        }  

        gsl::span<gfx::Material* const> materials() {
            return _materials;
        }
        
        gsl::span<gfx::IVertexBuffer* const> vertexbuffers() {
            return _vertexBuffers;
        }

        std::optional<gfx::IIndexBuffer*>& indexbuffer() {
            return _indexBuffer;
        }

        gsl::span<DrawableFragment> fragments() {
            return _fragments;
        }

    protected:

        gfx::IDevice& _device;
        
        gfx::IRenderState*              _state; 

        std::vector<gfx::Material*>         _materials;
        std::vector<gfx::IVertexBuffer*>    _vertexBuffers;  
        std::optional<gfx::IIndexBuffer*>   _indexBuffer;  
        std::vector<DrawableFragment>       _fragments;
    };
}



