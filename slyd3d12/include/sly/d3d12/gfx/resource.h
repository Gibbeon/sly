#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;
        class D3D12ResourceImpl : public IResource  {
        public:
            D3D12ResourceImpl(D3D12DeviceImpl& device);
            virtual void init(ResourceDesc& desc);

            ID3D12Resource& getID3D12Resource() { return *_resource; }
            size_t getBufferLocation() { return _bufferLocation; }
            size_t getSizeInBytes() { return _sizeInBytes; }
            size_t getStrideInBytes() { return  _strideInBytes; }

            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            virtual IDevice& getDevice() { return *_device; } 
                       
        protected:
            virtual void write(vptr_t data, size_t count, size_t stride);

        private:
            D3D12DeviceImpl* _device; 
            ID3D12Resource* _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
            size_t _strideInBytes;
        };
    }
}