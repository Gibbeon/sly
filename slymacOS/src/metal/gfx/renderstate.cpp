#include "sly/metal/gfx/renderstate.h"
#include "sly/metal/gfx/shader.h"
#include "sly/metal/gfx/convert.h"
#include "sly/metal/dxh.h"

using namespace sly::gfx;

METALRenderStateImpl::METALRenderStateImpl(METALDeviceImpl& device) : 
    //_pipelineState(nullptr), 
    _device(device) {

}

void METALRenderStateImpl::init(RenderStateDesc& desc) {
    /*CD3DX12_ROOT_SIGNATURE_DESC rootSignature;
    rootSignature.Init(0, nullptr, 0, nullptr, METAL_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    METALSerializeRootSignature(&rootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    getIMETALDevice().CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_IMETALRootSignature, reinterpret_cast<vptr_t*>(&_rootSignature));
   
    for(size_t i = 0; i < desc.inputElementCount; i++) {
        _inputElement[i] = METAL_INPUT_ELEMENT_DESC_CAST(desc.inputElements[i]);
    }

    METAL_GRAPHICS_PIPELINE_STATE_DESC pso = {};
    pso.InputLayout = { _inputElement, (UINT)desc.inputElementCount };
    pso.pRootSignature = _rootSignature;

    METALShaderImpl* vsd3dShader = reinterpret_cast<METALShaderImpl*>(desc.vsShader);
    METALShaderImpl* psd3dShader = reinterpret_cast<METALShaderImpl*>(desc.psShader);


    pso.VS = { vsd3dShader->getBuffer(), vsd3dShader->getSizeInBytes() };
    pso.PS = { psd3dShader->getBuffer(), psd3dShader->getSizeInBytes() };
    pso.RasterizerState = CD3DX12_RASTERIZER_DESC(METAL_DEFAULT);
    pso.BlendState = CD3DX12_BLEND_DESC(METAL_DEFAULT);
    pso.DepthStencilState.DepthEnable = FALSE;
    pso.DepthStencilState.StencilEnable = FALSE;
    pso.SampleMask = UINT_MAX;
    pso.PrimitiveTopologyType = METAL_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pso.NumRenderTargets = 1;
    pso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pso.SampleDesc.Count = 1;

    getIMETALDevice().CreateGraphicsPipelineState(&pso, IID_IMETALPipelineState, reinterpret_cast<vptr_t*>(&_pipelineState));
*/
}