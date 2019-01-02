#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/shader.h"

namespace sly {
    namespace gfx {
    
        class D3D12ShaderImpl : public IShader {
        public:
            D3D12ShaderImpl(D3D12DeviceImpl& device) : _device(&device) {}
            virtual void init(ShaderDesc& desc);

            void* getBuffer() { return _data->GetBufferPointer(); }
            size_t getSizeInBytes() { return _data->GetBufferSize(); }

            virtual void write(void* data, size_t size, size_t stride) {}
            
            D3D12DeviceImpl& getDevice() { return *_device; }
        
        protected:
            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            ID3DBlob* _data;
            D3D12DeviceImpl* _device;           
            
            using IShader::IShader;
        };
    }
}
