#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandlist.h"

using namespace sly::gfx;

D3D12CommandQueueImpl::D3D12CommandQueueImpl(ref_t<D3D12DeviceImpl> device, ref_t<CommandQueueDesc> desc) :
    D3D12ManagedImpl(device),
    fence_(device) 
{
    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    device->getID3D12Device()->CreateCommandQueue(&queueDesc, IID_ID3D12CommandQueue, reinterpret_cast<void**>(&queue_));
}
    
void D3D12CommandQueueImpl::executeCommandList(ref_t<ICommandList> lists) {
    queue_->ExecuteCommandLists(1, lists.as<D3D12CommandListImpl>()->getID3D12CommandList());
}