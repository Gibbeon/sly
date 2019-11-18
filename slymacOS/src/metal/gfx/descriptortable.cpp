#include "sly/metal/gfx/descriptortable.h"
#include "sly/metal/gfx/device.h"

using namespace sly::gfx;

METALDescriptorTableImpl::METALDescriptorTableImpl(METALDeviceImpl& device) : 
    _device(&device),
    _capacity(0),
    _nextFree(0),
    _count(0)
{
}

void METALDescriptorTableImpl::init(METALDescriptorTableDesc& desc) {
    //_capacity = desc.capacity;
    //_used.assign(_capacity, false);

    // ribe and create a render target view (RTV) descriptor heap.
    //METAL_DESCRIPTOR_HEAP_DESC rtvHeap = {};
    //rtvHeap.NumDescriptors = (UINT)desc.capacity; // one descriptor per buffer
    //rtvHeap.Type = METAL_DESCRIPTOR_HEAP_TYPE_RTV; // render target view
    //rtvHeap.Flags = METAL_DESCRIPTOR_HEAP_FLAG_NONE;
    //getIMETALDevice().CreateDescriptorHeap(&rtvHeap, IID_IMETALDescriptorHeap, reinterpret_cast<vptr_t*>(&_descHeap)); // creates a new heap just for this swap chain
    //_descHeapStride = getIMETALDevice().GetDescriptorHandleIncrementSize(METAL_DESCRIPTOR_HEAP_TYPE_RTV); // gets the stride of each descriptor
}

void METALDescriptorTableImpl::alloc(size_t* indicies, size_t count) {
    //for(size_t i = 0; i < count; ++i)
    //{
    //    indicies[i] = _nextFree;
    //    _used[_nextFree] = true;
    //    _nextFree = getNextFree();
   // }
    //_count += count;
}

void METALDescriptorTableImpl::free(size_t* indicies, size_t count) {
    //for(size_t i = 0; i < count; ++i)
    //{
    //    if(_used[indicies[i]])
    //    {
    //        _used[indicies[i]] = false;
    //        _count--; // only decrement if it was actually in use
    //    }
        
    //    if(_nextFree > indicies[i])
    //        _nextFree = indicies[i];
    //}
}
size_t METALDescriptorTableImpl::getAt(size_t index) {
    //return _descHeap->GetCPUDescriptorHandleForHeapStart().ptr + (index * _descHeapStride);

    return 0; //todo
}

size_t METALDescriptorTableImpl::getNextFree() {
    //for(size_t i = _nextFree; i < _capacity; ++i)
    //{
    //    if(!_used[i])
    //        return i;
    //}
    //return -1;


    return 0; //todo
    
}

