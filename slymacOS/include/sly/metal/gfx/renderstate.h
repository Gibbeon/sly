#pragma once

#include "sly/metal.h"
#include "sly/metal/gfx/device.h"
#include "sly/gfx/renderstate.h"

namespace sly {
    namespace gfx {

        class METALDeviceImpl;

        class METALRenderStateImpl : public IRenderState {
        public:
            METALRenderStateImpl(METALDeviceImpl& device);
            virtual void init(RenderStateDesc& desc);

            //ID3D12PipelineState&  getID3D12PipelineState() { return *_pipelineState; }
            //ID3D12RootSignature&  getID3D12RootSignature() { return *_rootSignature; }
        
        protected:
            void initRootSignature();
            void initPipelineState();

        private:                
            virtual IDevice& getDevice() { return *_device; } 
            //ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            METALDeviceImpl* _device;     

            //ID3D12PipelineState* _pipelineState;
            //ID3D12RootSignature* _rootSignature;  

            //METAL_INPUT_ELEMENT_DESC _inputElement[8];
        };       
    }
}