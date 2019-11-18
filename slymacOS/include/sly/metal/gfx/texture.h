#pragma once

#include "sly/metal.h"
#include "sly/metal/gfx/resource.h"
#include "sly/gfx/texture.h"

namespace sly {
    namespace gfx {
        class METALTextureImpl : public ITexture {
        public:
            virtual IDevice& getDevice() { return *_device; } 
            
            METALDeviceImpl* _device;
        };  
    }
}

