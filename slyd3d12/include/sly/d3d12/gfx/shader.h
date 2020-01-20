#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/shader.h"

namespace sly {
    namespace gfx {
    
        class D3D12ShaderImpl : public IShader {
        public:
            D3D12ShaderImpl(D3D12DeviceImpl& device);
            virtual ~D3D12ShaderImpl();

            virtual retval<void> init(const ShaderDesc& desc = ShaderBuilder().build());
            virtual retval<void> release();

            vptr_t getBuffer() { return _data->GetBufferPointer(); }
            size_t getSizeInBytes() { return _data->GetBufferSize(); }

            virtual void write(vptr_t data, size_t size, size_t stride) {}
            
            virtual IDevice& getDevice() { return _device; } 
        
        protected:
            ID3D12Device& getID3D12Device()   { return _device.getID3D12Device(); }
            gsl::owner<ID3DBlob*> _data;
            D3D12DeviceImpl& _device; 

            bool_t _initialized;          
            
            using IShader::IShader;
        };
    }
}
