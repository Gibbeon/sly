#pragma once

#include "sly/metal.h"
#include "sly/metal/gfx/resource.h"
#include "sly/gfx/shader.h"

namespace sly {
    namespace gfx {
    
        class METALShaderImpl : public IShader {
        public:
            METALShaderImpl(METALDeviceImpl& device) : _device(&device) {}
            virtual void init(ShaderDesc& desc);

            vptr_t getBuffer() { return nullptr; } //_data->GetBufferPointer(); }
            size_t getSizeInBytes() { return 0; } //_data->GetBufferSize(); }

            virtual void write(vptr_t data, size_t size, size_t stride) {}
            
            virtual IDevice& getDevice() { return *_device; } 
        
        protected:
            //ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            //ID3DBlob* _data;
            METALDeviceImpl* _device;           
            
            using IShader::IShader;
        };
    }
}
