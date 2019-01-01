#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/vertexbuffer.h"

namespace sly {
    namespace gfx {
        class D3D12VertexBufferImpl : public D3D12ManagedImpl, public IVertexBuffer {
        public:
            D3D12VertexBufferImpl(ref_t<D3D12DeviceImpl> device);

            virtual void init(ref_t<VertexBufferDesc> desc = VertexBufferDesc());

            virtual void write(ptr_t data, size_t size, size_t stride);

            ref_t<ID3D12Resource> getID3D12Resource() { return resource_; }
            size_t getBufferLocation() { return bufferLocation_; }
            size_t getSizeInBytes() { return sizeInBytes_; }
            size_t getStrideInBytes() { return strideInBytes_; }
             
        protected:
           // virtual void write(ptr_t data, size_t count, size_t stride);
            using D3D12ManagedImpl::D3D12ManagedImpl;

        private:
            ref_t<ID3D12Resource> resource_;
            size_t bufferLocation_;
            size_t sizeInBytes_;
            size_t strideInBytes_;
        };
    }
}

