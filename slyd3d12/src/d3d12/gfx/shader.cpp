#include "sly/d3d12/gfx/shader.h"

using namespace sly::gfx;

D3D12ShaderImpl::D3D12ShaderImpl(D3D12DeviceImpl& device) : _device(device), _initialized(false) {

}

D3D12ShaderImpl::~D3D12ShaderImpl() {
    Expects(!_initialized);
}

sly::retval<void> D3D12ShaderImpl::init(const ShaderDesc& desc) {
    ID3DBlob* errors;

    HRESULT hr = D3DCompile(desc.data.data(), desc.size, nullptr, nullptr, nullptr, desc.entry.c_str(), desc.target.c_str(), 0, 0, &_data, &errors);

    if (errors)
    {
        // The message is a 'warning' from the HLSL compiler.
        char const* message =
            static_cast<char const*>(errors->GetBufferPointer());

            return failed<void>(hr, message);
    }


    _initialized = true;
    return success();
}

sly::retval<void> D3D12ShaderImpl::release() {
    if(_initialized) {
        _data->Release();
        _initialized = false;
    }
    return success();
}

