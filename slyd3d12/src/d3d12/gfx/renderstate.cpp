#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/gfx/rootsignature.h"
#include "sly/d3d12/dxh.h"
#include "sly/win32.h"

using namespace sly::gfx;

D3D12RenderStateImpl::D3D12RenderStateImpl(D3D12DeviceImpl& device) : _pipelineState(nullptr), _device(&device), _initialized(false) {

}

sly::retval<void> D3D12RenderStateImpl::init(const RenderStateDesc& desc) {
    // root signature create needs to be pulled out of here
    

    D3D12_INPUT_ELEMENT_DESC inputElement[8];
    sly::gfx::IRootSignature* pRootSignature = desc.pRootSignature;

    if(pRootSignature == nullptr) {
        pRootSignature = getDevice().createRootSignature(desc.signature);
    }

       // create a PSO convert 
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso {};

    D3DAssign(pso, desc);
    
    pso.InputLayout.pInputElementDescs  = inputElement;
    pso.pRootSignature                  = _rootSignature = reinterpret_cast<D3D12RootSignatureImpl*>(pRootSignature)->getID3D12RootSignature();

    for(size_t i = 0; i < desc.inputElements.size(); i++) {  
        D3DAssign(inputElement[i], desc.inputElements[i]);
    }

    pso.CachedPSO = D3D12_CACHED_PIPELINE_STATE();

    // warwp device only
    //pso.Flags = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG;

    pso.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

    ThrowIfFailed(getID3D12Device().CreateGraphicsPipelineState(&pso, IID_ID3D12PipelineState, reinterpret_cast<vptr_t*>(&_pipelineState)));

    _initialized = true;

    return success();
}

sly::retval<void> D3D12RenderStateImpl::release() {
    Expects(_initialized);

    if(_initialized) {
        _pipelineState->Release();
        _rootSignature->Release();
        _initialized = false;
    }

    return success();
}