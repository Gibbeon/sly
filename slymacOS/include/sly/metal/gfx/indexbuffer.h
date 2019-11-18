#pragma once

#include "sly/metal.h"
#include "sly/gfx/indexbuffer.h"
#include "sly/metal/gfx/resource.h"

namespace sly {
    namespace gfx {
        class METALIndexBufferImpl : public IIndexBuffer {
        public:
            METALIndexBufferImpl(METALDeviceImpl& device);
            virtual void init(IndexBufferDesc& desc);

            virtual IDevice& getDevice() { return *_device; } 
                
        protected:
        
            METALDeviceImpl* _device;
        
        };
    }
}

