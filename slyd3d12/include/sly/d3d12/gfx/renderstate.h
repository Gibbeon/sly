#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;

        class D3D12RenderStateImpl : public D3D12ManagedImpl, public IRenderState {
        public:
            D3D12RenderStateImpl(ref_t<D3D12DeviceImpl> device);
            virtual void init(ref_t<RenderStateDesc> desc);

            ref_t<ID3D12PipelineState>  getID3D12PipelineState() { return pipelineState_; }
            ref_t<ID3D12RootSignature>  getID3D12RootSignature() { return rootSignature_; }
        
        protected:
            void initRootSignature();
            void initPipelineState();

        private:                
            ref_t<ID3D12PipelineState> pipelineState_;
            ref_t<ID3D12RootSignature> rootSignature_;  

            D3D12_INPUT_ELEMENT_DESC inputElementDesc_[8];
        };       
    }
}