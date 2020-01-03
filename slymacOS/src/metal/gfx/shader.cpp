#include "sly/metal/gfx/shader.h"

#include "mtlpp/mtlpp.hpp"
#include <stdio.h>

using namespace sly::gfx;

void METALShaderImpl::init(ShaderDesc& desc) {
    _library = getMETALDevice().NewLibrary(reinterpret_cast<const char*>(desc.data), mtlpp::CompileOptions(), nullptr);
    _data = _library.NewFunction(desc.entry.c_str());


    
    /*ID3DBlob* errors;

    HRESULT hr = D3DCompile(desc.data, desc.size, nullptr, nullptr, nullptr, desc.entry.c_str(), desc.target.c_str(), 0, 0, &_data, &errors);

    if(FAILED(hr)){
        const char* data = (const char*)errors->GetBufferPointer();
        std::string message(data);
    }*/
}

