#include "sly/d3d12/gfx/shader.h"

using namespace sly::gfx;

void D3D12ShaderImpl::init(ShaderDesc& desc) {
    
    ID3DBlob* errors;

    HRESULT hr = D3DCompile(desc.data, desc.size, nullptr, nullptr, nullptr, desc.entry.c_str(), desc.target.c_str(), 0, 0, &_data, &errors);

    if(FAILED(hr)){
        const char* data = (const char*)errors->GetBufferPointer();
        std::string message(data);
    }
}

