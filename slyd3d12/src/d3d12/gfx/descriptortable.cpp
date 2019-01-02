#include "sly/d3d12/gfx/descriptortable.h"
#include "sly/d3d12/gfx/device.h"

using namespace sly::gfx;

D3D12DescriptorTableImpl::D3D12DescriptorTableImpl(D3D12DeviceImpl& device) : 
    D3D12ManagedImpl(device),
    _capacity(0),
    _nextFree(0),
    _count(0)
{
}

void D3D12DescriptorTableImpl::init(D3D12DescriptorTableDesc& desc) {
    _capacity = desc.capacity;
    _used.assign(_capacity, false);

    // Describe and create a render target view (RTV) descriptor heap.
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = (UINT)desc.capacity; // one descriptor per buffer
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // render target view
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    getID3D12Device().CreateDescriptorHeap(&rtvHeapDesc, IID_ID3D12DescriptorHeap, reinterpret_cast<void**>(&_descHeap)); // creates a new heap just for this swap chain
    _descHeapStride = getID3D12Device().GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV); // gets the stride of each descriptor
}

void D3D12DescriptorTableImpl::alloc(size_t* indicies, size_t count) {
    for(size_t i = 0; i < count; ++i)
    {
        indicies[i] = _nextFree;
        _used[_nextFree] = true;
        _nextFree = getNextFree();
    }
    _count += count;
}

void D3D12DescriptorTableImpl::free(size_t* indicies, size_t count) {
    for(size_t i = 0; i < count; ++i)
    {
        if(_used[indicies[i]])
        {
            _used[indicies[i]] = false;
            _count--; // only decrement if it was actually in use
        }
        
        if(_nextFree > indicies[i])
            _nextFree = indicies[i];
    }
}
size_t D3D12DescriptorTableImpl::getAt(size_t index) {
    return _descHeap->GetCPUDescriptorHandleForHeapStart().ptr + (index * _descHeapStride);
}

size_t D3D12DescriptorTableImpl::getNextFree() {
    for(size_t i = _nextFree; i < _capacity; ++i)
    {
        if(!_used[i])
            return i;
    }
    return -1;
}

