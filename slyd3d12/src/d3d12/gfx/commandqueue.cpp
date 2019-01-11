#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandlist.h"

using namespace sly::gfx;

D3D12CommandQueueImpl::D3D12CommandQueueImpl(D3D12DeviceImpl& device):
    _device(&device),
    _fence(device) 
{

}

void D3D12CommandQueueImpl::init(CommandQueueDesc& desc) {
    // ribe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queue = {};
    queue.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queue.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    FenceBuilder f;
    _fence.init(f.build());

    getID3D12Device().CreateCommandQueue(&queue, IID_ID3D12CommandQueue, reinterpret_cast<vptr_t*>(&_queue));
}
    
void D3D12CommandQueueImpl::executeCommandList(ICommandList* lists, size_t count) {
    auto f =  &reinterpret_cast<D3D12CommandListImpl*>(lists)->getID3D12CommandList();
    _queue->ExecuteCommandLists(1, &f);

}

void D3D12CommandQueueImpl::flush() {
    _fence.waitFor(_queue);
}