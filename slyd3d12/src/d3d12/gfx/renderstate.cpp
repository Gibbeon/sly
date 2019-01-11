#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/dxh.h"

using namespace sly::gfx;

D3D12RenderStateImpl::D3D12RenderStateImpl(D3D12DeviceImpl& device) : _pipelineState(nullptr), _device(&device) {

}

void D3D12RenderStateImpl::init(RenderStateDesc& desc) {
    CD3DX12_ROOT_SIGNATURE_DESC rootSignature;
    rootSignature.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    D3D12SerializeRootSignature(&rootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    getID3D12Device().CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<vptr_t*>(&_rootSignature));
   
    for(size_t i = 0; i < desc.inputElementCount; i++) {
        _inputElement[i] = D3D12_INPUT_ELEMENT_DESC_CAST(desc.inputElements[i]);
    }

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso = {};
    pso.InputLayout = { _inputElement, (UINT)desc.inputElementCount };
    pso.pRootSignature = _rootSignature;

    D3D12ShaderImpl* vsd3dShader = reinterpret_cast<D3D12ShaderImpl*>(desc.vsShader);
    D3D12ShaderImpl* psd3dShader = reinterpret_cast<D3D12ShaderImpl*>(desc.psShader);


    pso.VS = { vsd3dShader->getBuffer(), vsd3dShader->getSizeInBytes() };
    pso.PS = { psd3dShader->getBuffer(), psd3dShader->getSizeInBytes() };
    pso.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    pso.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    pso.DepthStencilState.DepthEnable = FALSE;
    pso.DepthStencilState.StencilEnable = FALSE;
    pso.SampleMask = UINT_MAX;
    pso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pso.NumRenderTargets = 1;
    pso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pso.SampleDesc.Count = 1;

    getID3D12Device().CreateGraphicsPipelineState(&pso, IID_ID3D12PipelineState, reinterpret_cast<vptr_t*>(&_pipelineState));
}