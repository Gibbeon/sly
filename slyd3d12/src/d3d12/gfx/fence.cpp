#include "sly/d3d12/gfx/fence.h"
#include "sly/d3d12/gfx/device.h"

using namespace sly::gfx;

D3D12FenceImpl::D3D12FenceImpl(D3D12DeviceImpl& device):
    _device(&device), _initialized(false)
{
}

sly::retval<void> D3D12FenceImpl::init(const FenceDesc& desc)
{
    getID3D12Device().CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, reinterpret_cast<vptr_t*>(&_fence));
    _fenceValue = 1;
    _fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    
    _initialized = true;
    return success();
}

sly::retval<void> D3D12FenceImpl::release() {
    if(_initialized) {
        CloseHandle(_fenceEvent);
        _fence->Release();
        _initialized = false;
    }
    return success();
}

void D3D12FenceImpl::wait(size_t timeout) 
{
    // Signal and increment the fence value.
    _fence->Signal(_fenceValue);
    
    // Wait until the previous frame is finished.
    if (_fence->GetCompletedValue() < _fenceValue)
    {
        // Wait until the fence is completed.
        _fence->SetEventOnCompletion(_fenceValue, _fenceEvent);
        WaitForSingleObject(_fenceEvent, (DWORD)timeout);
    }

    _fenceValue++;
}

