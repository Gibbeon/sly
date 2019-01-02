#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/dxh.h"

using namespace sly::gfx;

D3D12RenderStateImpl::D3D12RenderStateImpl(D3D12DeviceImpl& device) : _pipelineState(nullptr), _device(&device) {

}

void D3D12RenderStateImpl::init(RenderStateDesc& desc) {
    CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    getID3D12Device().CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<vptr_t*>(&_rootSignature));
   
    for(size_t i = 0; i < desc.inputElementCount; i++) {
        _inputElementDesc[i] = D3D12_INPUT_ELEMENT_DESC_CAST(desc.inputElements[i]);
    }

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { _inputElementDesc, (UINT)desc.inputElementCount };
    psoDesc.pRootSignature = _rootSignature;

    D3D12ShaderImpl* vsd3dShader = reinterpret_cast<D3D12ShaderImpl*>(desc.vsShader);
    D3D12ShaderImpl* psd3dShader = reinterpret_cast<D3D12ShaderImpl*>(desc.psShader);


    psoDesc.VS = { vsd3dShader->getBuffer(), vsd3dShader->getSizeInBytes() };
    psoDesc.PS = { psd3dShader->getBuffer(), psd3dShader->getSizeInBytes() };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    getID3D12Device().CreateGraphicsPipelineState(&psoDesc, IID_ID3D12PipelineState, reinterpret_cast<vptr_t*>(&_pipelineState));
}