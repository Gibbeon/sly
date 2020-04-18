#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/indexbuffer.h"

namespace sly {
    namespace gfx {
        class D3D12IndexBufferImpl : public IIndexBuffer {
        public:
            D3D12IndexBufferImpl(D3D12DeviceImpl& device);
            virtual void init(BufferDesc& desc);

            virtual IDevice& getDevice() { return *_device; }

        protected:
            D3D12DeviceImpl* _device;
        };
    }   // namespace gfx
}   // namespace sly
