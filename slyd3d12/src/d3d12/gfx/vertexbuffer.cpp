#include "sly/d3d12/gfx/vertexbuffer.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/dxh.h"


using namespace sly::gfx;

D3D12VertexBufferImpl::D3D12VertexBufferImpl(D3D12DeviceImpl& device) :
    _device(&device) 
{

}


            
IDevice& D3D12VertexBufferImpl::getDevice() 
{ 
    return *_device; 
} 

void D3D12VertexBufferImpl::init(VertexBufferDesc& desc) {

    getID3D12Device().CreateCommittedResource(
         &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
         D3D12_HEAP_FLAG_NONE,
         &CD3DX12_RESOURCE_DESC::Buffer(desc.sizeInBytes),
         D3D12_RESOURCE_STATE_GENERIC_READ,
         nullptr,
         IID_ID3D12Resource, 
         reinterpret_cast<vptr_t*>(&_resource));
    
    write(desc.data, desc.sizeInBytes, desc.stride);
}

void D3D12VertexBufferImpl::write(vptr_t data, size_t size, size_t stride) {
    byte_t* dest;
    D3D12_RANGE readRange = {0, 0};        // We do not intend to read from this resource on the CPU.
    _resource->Map(0, &readRange, reinterpret_cast<vptr_t*>(&dest));
    memcpy(dest, data, size);
    _resource->Unmap(0, nullptr);
    
    _bufferLocation = (uint_t)_resource->GetGPUVirtualAddress();
    _sizeInBytes = size;
    _strideInBytes = stride;
}

/* #include "te/d3d12/dxh.h"
#include "te/d3d12/vertexbuffer.h"

using namespace te;

D3D12VertexBuffer::D3D12VertexBuffer(ID3D12Resource* buffer, ulong_t size) :
    _buffer(buffer),
    _size(size) {

}

bool_t D3D12VertexBuffer::Write(vptr_t data, ulong_t offset, ulong_t size) {
    float m_aspectRatio = 768.0 / 1024.0;
    // Define the geometry for a triangle.
    Vertex triangleVertices[] =
    {
        { { 0.0f, 0.25f * (m_aspectRatio), 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { 0.25f, -0.25f * m_aspectRatio, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.25f, -0.25f * m_aspectRatio, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };

    const UINT vertexBufferSize = sizeof(triangleVertices);

    // Copy the triangle data to the vertex buffer.
    UINT8* pVertexDataBegin;
    CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.
    ThrowIfFailed(_buffer->Map(0, &readRange, reinterpret_cast<vptr_t*>(&pVertexDataBegin)));
    memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
    _buffer->Unmap(0, nullptr);

    // Initialize the vertex buffer view.
    _vertexBufferView.BufferLocation = _buffer->GetGPUVirtualAddress();
    _vertexBufferView.StrideInBytes = sizeof(Vertex);
    _vertexBufferView.SizeInBytes = vertexBufferSize;
    
    return true;
} */