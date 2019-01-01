#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;
        class D3D12ResourceImpl : public D3D12ManagedImpl  {
        public:
            D3D12ResourceImpl(ref_t<D3D12DeviceImpl> device);
            virtual void init(ref_t<ResourceDesc> desc = IResource::DEFAULT_DESC);

            ref_t<ID3D12Resource> getID3D12Resource() { return resource_; }
            size_t getBufferLocation() { return bufferLocation_; }
            size_t getSizeInBytes() { return sizeInBytes_; }
            size_t getStrideInBytes() { return strideInBytes_; }
                       
        protected:
            virtual void write(ptr_t data, size_t count, size_t stride);
            using D3D12ManagedImpl::D3D12ManagedImpl;

        private:
            ref_t<ID3D12Resource> resource_;
            size_t bufferLocation_;
            size_t sizeInBytes_;
            size_t strideInBytes_;
        };
    }
}