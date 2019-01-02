#pragma once

#include "sly/d3d12.h"
#include "sly/gfx/indexbuffer.h"
#include "sly/d3d12/gfx/resource.h"

namespace sly {
    namespace gfx {
        class D3D12IndexBufferImpl : public IIndexBuffer {
        public:
            D3D12IndexBufferImpl(D3D12DeviceImpl& device);
            virtual void init(IndexBufferDesc& desc);

            virtual IDevice& getDevice() { return *_device; } 
                
        protected:
        
            D3D12DeviceImpl* _device;
        
        };
    }
}

