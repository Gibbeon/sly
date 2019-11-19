#pragma once

#include "sly/metal.h"
#include "sly/metal/gfx/resource.h"
#include "sly/gfx/vertexbuffer.h"

namespace sly {
    namespace gfx {
        class METALVertexBufferImpl : public IVertexBuffer {
        public:
            METALVertexBufferImpl(METALDeviceImpl& device);

            virtual void init(VertexBufferDesc& desc);

            virtual void write(vptr_t data, size_t size, size_t stride);

            mtlpp::Buffer& getMETALResource() { return _resource; }
            virtual size_t getBufferLocation() { return _bufferLocation; }
            virtual size_t getSizeInBytes() { return _sizeInBytes; }
            virtual size_t getStrideInBytes() { return _strideInBytes; }

            
            virtual IDevice& getDevice();

        protected:
            
            //ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            METALDeviceImpl* _device;     

        private:
            mtlpp::Buffer _resource;
            //ID3D12Resource* _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
            size_t _strideInBytes;
        };
    }
}

