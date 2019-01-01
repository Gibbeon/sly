#pragma once

#include "sly/global.h"
#include "sly/gfx/device.h"
#include "sly/d3d12/gfx/device.h"

namespace sly {
    namespace gfx {
        class D3D12DeviceImpl;
        class D3D12ManagedImpl {
        public:
            ref_t<D3D12DeviceImpl> getDevice() { return device_; }

        protected:
            D3D12ManagedImpl(ref_t<D3D12DeviceImpl> device) : device_(device) {} // require the storage of the calling device
            //virtual ~D3D12ManagedImpl() {}

            ref_t<ID3D12Device> getID3D12Device()   { return device_->getID3D12Device(); }

        private:
            D3D12ManagedImpl() {}
            D3D12ManagedImpl(const D3D12ManagedImpl&) {}

            ref_t<D3D12DeviceImpl> device_;            
        };
    }
}