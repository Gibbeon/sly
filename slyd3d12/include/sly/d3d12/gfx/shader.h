#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/shader.h"

namespace sly {
    namespace gfx {
    
        class D3D12ShaderImpl : public IShader {
        public:
            D3D12ShaderImpl(ref_t<D3D12DeviceImpl> device) : device_(device) {}
            virtual void init(ref_t<ShaderDesc> desc = IShader::DEFAULT_DESC);

            ptr_t getBuffer() { return data_->GetBufferPointer(); }
            size_t getSizeInBytes() { return data_->GetBufferSize(); }

            virtual void write(ptr_t data, size_t size, size_t stride) {}
            

            ref_t<D3D12DeviceImpl> getDevice() { return device_; }
        
        protected:
            ref_t<ID3D12Device> getID3D12Device()   { return device_->getID3D12Device(); }
            ref_t<ID3DBlob> data_;
            ref_t<D3D12DeviceImpl> device_;           
            
            using IShader::IShader;
        };
    }
}
