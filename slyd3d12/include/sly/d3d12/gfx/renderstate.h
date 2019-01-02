#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;

        class D3D12RenderStateImpl : public D3D12ManagedImpl, public IRenderState {
        public:
            D3D12RenderStateImpl(D3D12DeviceImpl& device);
            virtual void init(RenderStateDesc& desc);

            ID3D12PipelineState&  getID3D12PipelineState() { return *_pipelineState; }
            ID3D12RootSignature&  getID3D12RootSignature() { return *_rootSignature; }
        
        protected:
            void initRootSignature();
            void initPipelineState();

        private:                
            ID3D12PipelineState* _pipelineState;
            ID3D12RootSignature* _rootSignature;  

            D3D12_INPUT_ELEMENT_DESC _inputElementDesc[8];
        };       
    }
}