

#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        class D3D12RenderTargetImpl : public IRenderTarget {
        public:
            D3D12RenderTargetImpl() {}

            virtual retval<void> init(ID3D12Resource* ptr, size_t buffer){
                _resource = ptr;
                _bufferLocation = buffer;
                return success();
            }

            virtual retval<void> release() {
                _resource->Release();
                return success();
            }

            virtual void write(vptr_t data, size_t size, size_t stride) {
                
            }

            ID3D12Resource& getID3D12Resource() { return *_resource; }
            size_t getBufferLocation() {  return _bufferLocation; }
            size_t getSizeInBytes() {  return _sizeInBytes; }

            virtual IDevice& getDevice() { return *_device; } 

        protected:

        private:
            D3D12DeviceImpl* _device;
            gsl::owner<ID3D12Resource*> _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
        };
    }
}
