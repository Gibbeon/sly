#include "sly/metal/gfx/fence.h"
#include "sly/metal/gfx/device.h"

using namespace sly::gfx;

METALFenceImpl::METALFenceImpl(METALDeviceImpl& device):
    _device(&device) 
{
}

void METALFenceImpl::init( FenceDesc& desc)
{
    //getIMETALDevice().CreateFence(0, METAL_FENCE_FLAG_NONE, IID_IMETALFence, reinterpret_cast<vptr_t*>(&_fence));
    //_fenceValue = 1;
    //_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void METALFenceImpl::wait(size_t timeout) 
{
    // Signal and increment the fence value.
    //_fence->Signal(_fenceValue);
    
    // Wait until the previous frame is finished.
    //if (_fence->GetCompletedValue() < _fenceValue)
    //{
        // Wait until the fence is completed.
    //    _fence->SetEventOnCompletion(_fenceValue, _fenceEvent);
    //    WaitForSingleObject(_fenceEvent, (DWORD)timeout);
   // }

    //_fenceValue++;
}

