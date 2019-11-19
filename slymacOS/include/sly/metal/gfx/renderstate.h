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

            mtlpp::RenderPipelineState&  getMETALPipelineState() { return _pipelineState; }
            //ID3D12RootSignature&  getID3D12RootSignature() { return *_rootSignature; }
        
        protected:
            void initRootSignature();
            void initPipelineState();

        private:                
            virtual IDevice& getDevice() { return _device; } 
            mtlpp::Device& getMETALDevice()   { return _device.getMETALDevice(); }
            
            METALDeviceImpl& _device;     

            mtlpp::RenderPipelineState _pipelineState;
            //ID3D12PipelineState* _pipelineState;
            //ID3D12RootSignature* _rootSignature;  

            //METAL_INPUT_ELEMENT_DESC _inputElement[8];
        };       
    }
}