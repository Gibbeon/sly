#include "sly/d3d12/gfx/resource.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/dxh.h"


using namespace sly::gfx;

D3D12ResourceImpl::D3D12ResourceImpl(ref_t<D3D12DeviceImpl> device) :
    D3D12ManagedImpl(device) 
{
}


void D3D12ResourceImpl::init(ref_t<ResourceDesc> desc) {

    getID3D12Device()->CreateCommittedResource(
         &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
         D3D12_HEAP_FLAG_NONE,
         &CD3DX12_RESOURCE_DESC::Buffer(desc->sizeInBytes),
         D3D12_RESOURCE_STATE_GENERIC_READ,
         nullptr,
         IID_ID3D12Resource, 
         reinterpret_cast<void**>(&resource_));
    
    write(desc->data, desc->sizeInBytes, desc->stride);
}

void D3D12ResourceImpl::write(ptr_t data, size_t size, size_t stride) {
    ubyte* dest;
    CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.
    resource_->Map(0, &readRange, reinterpret_cast<void**>(&dest));
    Memory::copy(data, dest, size);
    resource_->Unmap(0, nullptr);
    
    bufferLocation_ = (uint_t)resource_->GetGPUVirtualAddress();
    sizeInBytes_ = size;
    strideInBytes_ = stride;
}


