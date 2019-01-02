#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/texture.h"

namespace sly {
    namespace gfx {
        class D3D12TextureImpl : public ITexture {
        public:
            virtual IDevice& getDevice() { return *_device; } 
            
            D3D12DeviceImpl* _device;
        };  
    }
}

