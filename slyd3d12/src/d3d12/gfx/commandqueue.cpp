#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandlist.h"

using namespace sly::gfx;

D3D12CommandQueueImpl::D3D12CommandQueueImpl(D3D12DeviceImpl& device):
    _device(&device),
    _fence(device) 
{

}

sly::retval<void> D3D12CommandQueueImpl::init(const CommandQueueDesc& desc) {
    // ribe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queue = {};
    queue.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queue.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    FenceBuilder f;
    _fence.init(f.build());

    getID3D12Device().CreateCommandQueue(&queue, IID_ID3D12CommandQueue, reinterpret_cast<vptr_t*>(&_queue));

    return success();
}

sly::retval<void> D3D12CommandQueueImpl::release() {
    _queue->Release();
    _fence.release();

    return success();
}
    
void D3D12CommandQueueImpl::executeCommandLists(gsl::span<const ICommandList* const> lists) {
    std::vector<ID3D12CommandList*> newV( lists.size() );
    auto lambda = [](const sly::gfx::ICommandList *const data) { return std::addressof(static_cast<D3D12CommandListImpl*>(const_cast<ICommandList*>(data))->getID3D12CommandList()); };

    std::transform( lists.begin(), lists.end(), newV.begin(), lambda );

    _queue->ExecuteCommandLists(lists.size(), newV.data());

}

void D3D12CommandQueueImpl::flush() {
    _fence.waitFor(_queue);
}