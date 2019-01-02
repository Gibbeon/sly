#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/vertexbuffer.h"

namespace sly {
    namespace gfx {
        class D3D12VertexBufferImpl : public IVertexBuffer {
        public:
            D3D12VertexBufferImpl(D3D12DeviceImpl& device);

            virtual void init(VertexBufferDesc& desc);

            virtual void write(vptr_t data, size_t size, size_t stride);

            ID3D12Resource& getID3D12Resource() { return *_resource; }
            virtual size_t getBufferLocation() { return _bufferLocation; }
            virtual size_t getSizeInBytes() { return _sizeInBytes; }
            virtual size_t getStrideInBytes() { return _strideInBytes; }

            
            virtual IDevice& getDevice();

        protected:
            
            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            D3D12DeviceImpl* _device;     

        private:
            ID3D12Resource* _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
            size_t _strideInBytes;
        };
    }
}

