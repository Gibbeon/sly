#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/dxh.h"
#include "sly/win32.h"

using namespace sly::gfx;

D3D12RenderStateImpl::D3D12RenderStateImpl(D3D12DeviceImpl& device) : _pipelineState(nullptr), _device(&device), _initialized(false) {

}

sly::retval<void> D3D12RenderStateImpl::init(const RenderStateDesc& desc) {
    // root signature create needs to be pulled out of here
    CD3DX12_ROOT_SIGNATURE_DESC rootSignature;
    rootSignature.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    ThrowIfFailed(D3D12SerializeRootSignature(&rootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
    ThrowIfFailed(getID3D12Device().CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<vptr_t*>(&_rootSignature)));
       

       // create a PSO convert 
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso {};

    D3DAssign(pso, desc);
    
    pso.InputLayout.pInputElementDescs = _inputElement;
    pso.pRootSignature = _rootSignature;

    for(size_t i = 0; i < desc.inputElements.size(); i++) {  
        D3DAssign(const_cast<D3D12_INPUT_ELEMENT_DESC*>(pso.InputLayout.pInputElementDescs)[i], desc.inputElements[i]);
    }

    pso.CachedPSO = D3D12_CACHED_PIPELINE_STATE();
    pso.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
    pso.DSVFormat = DXGI_FORMAT_UNKNOWN;

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