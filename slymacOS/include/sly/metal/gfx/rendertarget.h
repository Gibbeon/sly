

#pragma once

#include "sly/metal.h"
#include "sly/metal/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        class METALRenderTargetImpl : public IRenderTarget {
        public:
            METALRenderTargetImpl() {}

            //virtual void init(ID3D12Resource* ptr, size_t buffer){
            //    _resource = ptr;
            //    _bufferLocation = buffer;
            //}

            virtual void write(vptr_t data, size_t size, size_t stride) {
                
            }

            //ID3D12Resource& getID3D12Resource() { return *_resource; }
            size_t getBufferLocation() {  return _bufferLocation; }
            size_t getSizeInBytes() {  return _sizeInBytes; }

            virtual IDevice& getDevice() { return *_device; } 

        protected:

        private:
            METALDeviceImpl* _device;
            //ID3D12Resource* _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
        };
    }
}
