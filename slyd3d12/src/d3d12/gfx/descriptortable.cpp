#include "sly/d3d12/gfx/descriptortable.h"
#include "sly/d3d12/gfx/device.h"

using namespace sly::gfx;

D3D12DescriptorTableImpl::D3D12DescriptorTableImpl(D3D12DeviceImpl& device) : 
    _device(&device),
    _capacity(0),
    _nextFree(0),
    _count(0)
{
}

sly::retval<void> D3D12DescriptorTableImpl::init(const D3D12DescriptorTableDesc& desc) {
    _capacity = desc.capacity;
    _used.assign(_capacity, false);

    // ribe and create a render target view (RTV) descriptor heap.
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeap = {};
    rtvHeap.NumDescriptors = (UINT)desc.capacity; // one descriptor per buffer
    rtvHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // render target view
    rtvHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    getID3D12Device().CreateDescriptorHeap(&rtvHeap, IID_ID3D12DescriptorHeap, reinterpret_cast<vptr_t*>(&_descHeap)); // creates a new heap just for this swap chain
    _descHeapStride = getID3D12Device().GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV); // gets the stride of each descriptor
    return success();
}

sly::retval<void> D3D12DescriptorTableImpl::release() {
    _descHeap->Release();
    return success();
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

