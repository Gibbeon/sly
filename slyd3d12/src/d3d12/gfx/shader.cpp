#include "sly/d3d12/gfx/shader.h"

using namespace sly::gfx;

void D3D12ShaderImpl::init(ref_t<ShaderDesc> desc) {
    
    ID3DBlob* errors;

    HRESULT hr = D3DCompile(desc->data, desc->size, nullptr, nullptr, nullptr, desc->entry, desc->target, 0, 0, data_, &errors);

    if(FAILED(hr)){
        string_t messages = (char_t*)errors->GetBufferPointer();
        SYSTEM_HALT("DOOOM!");
    }
}

