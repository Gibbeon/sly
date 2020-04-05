#include "sly/d3d12/gfx/resource.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/dxh.h"


using namespace sly::gfx;

D3D12ResourceImpl::D3D12ResourceImpl(D3D12DeviceImpl& device) :
    _device(&device) 
{
}


void D3D12ResourceImpl::init(ResourceDesc& desc) {

    getID3D12Device().CreateCommittedResource(
         &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
         D3D12_HEAP_FLAG_NONE,
         &CD3DX12_RESOURCE_DESC::Buffer(desc.sizeInBytes),
         D3D12_RESOURCE_STATE_GENERIC_READ,
         nullptr,
         IID_ID3D12Resource, 
         reinterpret_cast<vptr_t*>(&_resource));
    
    write(desc.data.get(), desc.sizeInBytes, desc.stride);
}

void D3D12ResourceImpl::write(vptr_t data, size_t size, size_t stride) {
    byte_t* dest;
    D3D12_RANGE readRange = {0, 0};        // We do not intend to read from this resource on the CPU.
    _resource->Map(0, &readRange, reinterpret_cast<vptr_t*>(&dest));
    memcpy(dest, data, size);
    _resource->Unmap(0, nullptr);
    
    _bufferLocation = (uint_t)_resource->GetGPUVirtualAddress();
    _sizeInBytes = size;
    _strideInBytes = stride;
}


