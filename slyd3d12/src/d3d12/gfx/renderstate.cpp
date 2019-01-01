#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/dxh.h"

using namespace sly::gfx;

D3D12RenderStateImpl::D3D12RenderStateImpl(ref_t<D3D12DeviceImpl> device) : pipelineState_(nullptr), D3D12ManagedImpl(device) {

}

void D3D12RenderStateImpl::init(ref_t<RenderStateDesc> desc) {
    CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    getID3D12Device()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<void**>(&rootSignature_));
   
    for(int i = 0; i < desc->inputElementCount; i++) {
        inputElementDesc_[i] = D3D12_INPUT_ELEMENT_DESC_CAST(desc->inputElements[i]);
    }

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputElementDesc_, (UINT)desc->inputElementCount };
    psoDesc.pRootSignature = rootSignature_;

    IShader* shader = desc->vsShader.ptr();
    D3D12ShaderImpl* d3dShader = reinterpret_cast<D3D12ShaderImpl*>(shader);
    ptr_t val = d3dShader->getBuffer();

    psoDesc.VS = { desc->vsShader.as<D3D12ShaderImpl>()->getBuffer(), desc->vsShader.as<D3D12ShaderImpl>()->getSizeInBytes() };
    psoDesc.PS = { desc->psShader.as<D3D12ShaderImpl>()->getBuffer(), desc->psShader.as<D3D12ShaderImpl>()->getSizeInBytes() };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    getID3D12Device()->CreateGraphicsPipelineState(&psoDesc, IID_ID3D12PipelineState, reinterpret_cast<void**>(&pipelineState_));
}