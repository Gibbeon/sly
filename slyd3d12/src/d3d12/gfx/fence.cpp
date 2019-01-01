#include "sly/d3d12/gfx/fence.h"
#include "sly/d3d12/gfx/device.h"

using namespace sly::gfx;

D3D12FenceImpl::D3D12FenceImpl(ref_t<D3D12DeviceImpl> device, ref_t<FenceDesc> desc) :
    D3D12ManagedImpl(device) 
{
    device->getID3D12Device()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, reinterpret_cast<void**>(&fence_));
    fenceValue_ = 1;
    fenceEvent_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

   void D3D12FenceImpl::wait(size_t timeout) {
    // Signal and increment the fence value.
    fence_->Signal(fenceValue_);
    fenceValue_++;

    // Wait until the previous frame is finished.
    if (fence_->GetCompletedValue() < fenceValue_)
    {
        // Wait until the fence is completed.
        fence_->SetEventOnCompletion(fenceValue_, fenceEvent_);
        WaitForSingleObject(fenceEvent_, (DWORD)timeout);
    }
}

