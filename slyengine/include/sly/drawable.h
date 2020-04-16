#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/drawablefragment.h"

namespace sly {

    struct DrawableDesc : public sly::ISerializable {
    public:
        SLY_TYPEINFO;

        gfx::RenderStateDesc state;
        gfx::ePrimitiveType primitiveType;

        std::vector<gfx::BufferDesc> buffers;
        std::vector<gfx::ShaderDesc> shaders;
        DrawableFragmentDesc fragment;
        
        sly::retval<void> serialize(sly::ISerializer& archive) {
            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {
            {
                gfx::BufferDesc __desc;
                auto& __array = archive.open("buffers");
                for(size_t i = 0; i < __array.size(); i++) {
                    __array[i].read(__desc);
                    buffers.push_back(__desc);
                }
                __array.close();
            }

            {
                gfx::ShaderDesc __desc;
                auto& __array = archive.open("shaders");
                for(size_t i = 0; i < __array.size(); i++) {
                    __array[i].read(__desc);
                    shaders.push_back(__desc);
                }
                __array.close();
            }

            DESERIALIZE(state);
            DESERIALIZE(fragment);
            DESERIALIZE(primitiveType, gfx::ePrimitiveType_Default);

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
                        _vertexBuffers.push_back(vb);
                    break;
                }
            }

            DrawableFragment fragment;
            fragment.init(desc.fragment);
            _fragments.push_back(fragment);

            for(auto& shader: desc.shaders) {
                auto pShader = _device.createShader(shader);
                switch(shader.shaderType) {
                    case gfx::eShaderType_Vertex:
                        desc.state.vsShader = pShader;
                        break;
                    case gfx::eShaderType_Pixel:
                        desc.state.psShader = pShader;
                        break;
                    break;
                }
            }

            _state = _device.createRenderState(desc.state); 
            _primitiveType = desc.primitiveType;           
            return success();      

        }

        retval<void> draw(  gfx::ICommandList& list
                            , uint_t vertexSlot = 0) const {

            list.setRenderState(*_state);
            list.setPrimitiveType(_primitiveType);
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
        gfx::ePrimitiveType   _primitiveType;
    };
}



