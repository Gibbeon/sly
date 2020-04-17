#include "sly/d3d12/gfx/rootsignature.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/dxh.h"
#include "sly/win32.h"


using namespace sly::gfx;

D3D12RootSignatureImpl::D3D12RootSignatureImpl(D3D12DeviceImpl& device) :
    _device(&device) 
{
}


sly::retval<void> D3D12RootSignatureImpl::init(const RootSignatureDesc& desc) {
    // root signature create needs to be pulled out of here
    CD3DX12_ROOT_SIGNATURE_DESC rootSignature;
    D3DAssign(rootSignature, desc);

    D3D12_ROOT_PARAMETER        params[32];
    D3D12_STATIC_SAMPLER_DESC   samplers[32];
    D3D12_DESCRIPTOR_RANGE      ranges[32][32];

    for(size_t i = 0; i < desc.parameters.size(); i++) {
        D3DAssign(params[i], desc.parameters[i]);
        if(desc.parameters[i].parameterType == eRootParameterType_Descriptor_Table) {
            params[i].DescriptorTable.NumDescriptorRanges = (UINT)desc.parameters[i].descriptors.size();
            params[i].DescriptorTable.pDescriptorRanges = ranges[i];

            for(size_t j = 0; j < desc.parameters[i].descriptors.size(); j++) {
                D3DAssign(ranges[i][j], desc.parameters[i].descriptors[j]);
            }
        }
    }

    for(size_t i = 0; i < desc.staticSamplers.size(); i++) {
        D3DAssign(samplers[i], desc.staticSamplers[i]);
    }

    rootSignature.Init(
        (UINT)desc.parameters.size(), 
        params, 
        (UINT)desc.staticSamplers.size(), 
        samplers, 
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* errors;

    if(!SUCCEEDED(D3D12SerializeRootSignature(&rootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &errors))) {
        if (errors)
        {
            // The message is a 'warning' from the HLSL compiler.
            char const* message =
                static_cast<char const*>(errors->GetBufferPointer());

                LOG_DEBUG("%s", message);

                return failed<void>(1, message);
        }
    }
    ThrowIfFailed(getID3D12Device().CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<vptr_t*>(&_rootSignature)));
    return success();

}


