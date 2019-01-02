#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;
        class D3D12ResourceImpl : public D3D12ManagedImpl  {
        public:
            D3D12ResourceImpl(D3D12DeviceImpl& device);
            virtual void init(ResourceDesc& desc);

            ID3D12Resource& getID3D12Resource() { return *_resource; }
            size_t getBufferLocation() { return _bufferLocation; }
            size_t getSizeInBytes() { return _sizeInBytes; }
            size_t getStrideInBytes() { return  _strideInBytes; }
                       
        protected:
            virtual void write(void* data, size_t count, size_t stride);
            using D3D12ManagedImpl::D3D12ManagedImpl;

        private:
            ID3D12Resource* _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
            size_t _strideInBytes;
        };
    }
}