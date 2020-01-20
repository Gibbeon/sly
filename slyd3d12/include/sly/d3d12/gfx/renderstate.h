#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/gfx/renderstate.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;

        class D3D12RenderStateImpl : public IRenderState {
        public:
            D3D12RenderStateImpl(D3D12DeviceImpl& device);
            virtual retval<void> init(const RenderStateDesc& desc);
            virtual retval<void> release();

            ID3D12PipelineState&  getID3D12PipelineState() { return *_pipelineState; }
            ID3D12RootSignature&  getID3D12RootSignature() { return *_rootSignature; }
        
        protected:
            void initRootSignature();
            void initPipelineState();

        private:                
            virtual IDevice& getDevice() { return *_device; } 
            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            D3D12DeviceImpl* _device;     

            ID3D12PipelineState* _pipelineState;
            ID3D12RootSignature* _rootSignature;  

            bool_t _initialized;

            D3D12_INPUT_ELEMENT_DESC _inputElement[8];
        };       
    }
}