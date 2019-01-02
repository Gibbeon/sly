#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandlist.h"

using namespace sly::gfx;

D3D12CommandQueueImpl::D3D12CommandQueueImpl(D3D12DeviceImpl& device):
    D3D12ManagedImpl(device),
    _fence(device) 
{

}

void D3D12CommandQueueImpl::init(CommandQueueDesc& desc) {
    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    getID3D12Device().CreateCommandQueue(&queueDesc, IID_ID3D12CommandQueue, reinterpret_cast<void**>(&_queue));
}
    
void D3D12CommandQueueImpl::executeCommandList(ICommandList* lists, size_t count) {
    auto f =  &reinterpret_cast<D3D12CommandListImpl*>(lists)->getID3D12CommandList();
    _queue->ExecuteCommandLists(1, &f);
}