#pragma once

#include "sly/global.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/gfx/rootsignature.h"

namespace sly {
    namespace gfx {
        class D3D12RootSignatureImpl : public IRootSignature {
        public:
            D3D12RootSignatureImpl(D3D12DeviceImpl& device);
            virtual ~D3D12RootSignatureImpl() {}
            
            virtual retval<void> init(const RootSignatureDesc& desc) ;

            ID3D12RootSignature* getID3D12RootSignature() { return _rootSignature; }

        protected:
            D3D12RootSignatureImpl() {}

            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            D3D12DeviceImpl* _device;     

        private:            
            ID3D12RootSignature* _rootSignature; 

        };
    }
}
