#include "sly/metal/gfx/vertexbuffer.h"
#include "sly/metal/gfx/device.h"
#include "sly/metal/dxh.h"


using namespace sly::gfx;

METALVertexBufferImpl::METALVertexBufferImpl(METALDeviceImpl& device) :
    _device(&device) 
{

}
            
IDevice& METALVertexBufferImpl::getDevice() 
{ 
    return *_device; 
} 

void METALVertexBufferImpl::init(VertexBufferDesc& desc) {

    /*getIMETALDevice().CreateCommittedResource(
         &CD3DX12_HEAP_PROPERTIES(METAL_HEAP_TYPE_UPLOAD),
         METAL_HEAP_FLAG_NONE,
         &CD3DX12_RESOURCE_DESC::Buffer(desc.sizeInBytes),
         METAL_RESOURCE_STATE_GENERIC_READ,
         nullptr,
         IID_IMETALResource, 
         reinterpret_cast<vptr_t*>(&_resource));
    
    write(desc.data, desc.sizeInBytes, desc.stride);
    */
}

void METALVertexBufferImpl::write(vptr_t data, size_t size, size_t stride) {
    /*
    byte_t* dest;
    METAL_RANGE readRange = {0, 0};        // We do not intend to read from this resource on the CPU.
    _resource->Map(0, &readRange, reinterpret_cast<vptr_t*>(&dest));
    memcpy(dest, data, size);
    _resource->Unmap(0, nullptr);
    
    _bufferLocation = (uint_t)_resource->GetGPUVirtualAddress();
    _sizeInBytes = size;
    _strideInBytes = stride;
    */
}