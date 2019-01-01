#include "sly/d3d12/gfx/descriptortable.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/collections/array.h"
#include "sly/collections/fixedarray.h"

using namespace sly::gfx;

D3D12DescriptorTableImpl::D3D12DescriptorTableImpl(ref_t<D3D12DeviceImpl> device) : 
    D3D12ManagedImpl(device),
    capacity_(0),
    nextFree_(0),
    count_(0)
{
}

void D3D12DescriptorTableImpl::init(ref_t<D3D12DescriptorTableDesc> desc) {
    capacity_ = desc->capacity;
    used_.ensure(desc->capacity);
    used_.fillRange(false, desc->capacity);

    // Describe and create a render target view (RTV) descriptor heap.
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = (UINT)desc->capacity; // one descriptor per buffer
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // render target view
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    getID3D12Device()->CreateDescriptorHeap(&rtvHeapDesc, IID_ID3D12DescriptorHeap, reinterpret_cast<void**>(&descHeap_)); // creates a new heap just for this swap chain
    descHeapStride_ = getID3D12Device()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV); // gets the stride of each descriptor
}

void D3D12DescriptorTableImpl::alloc(sly::Array<size_t>& indicies, size_t count) {
    for(size_t i = 0; i < count; ++i)
    {
        indicies[i] = nextFree_;
        used_[nextFree_] = true;
        nextFree_ = getNextFree();
    }
    count_ += count;
}

void D3D12DescriptorTableImpl::free(sly::Array<size_t>& indicies, size_t count) {
    for(size_t i = 0; i < count; ++i)
    {
        if(used_[indicies[i]])
        {
            used_[indicies[i]] = false;
            count_--; // only decrement if it was actually in use
        }
        
        if(nextFree_ > indicies[i])
            nextFree_ = indicies[i];
    }
}
size_t D3D12DescriptorTableImpl::getAt(size_t index) {
    return descHeap_->GetCPUDescriptorHandleForHeapStart().ptr + (index * descHeapStride_);
}

size_t D3D12DescriptorTableImpl::getNextFree() {
    for(size_t i = nextFree_; i < capacity_; ++i)
    {
        if(!used_[i])
            return i;
    }
    return -1;
}

