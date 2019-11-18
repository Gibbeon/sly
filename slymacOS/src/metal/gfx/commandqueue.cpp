#include "sly/metal/gfx/commandqueue.h"
#include "sly/metal/gfx/device.h"
#include "sly/metal/gfx/commandlist.h"

using namespace sly::gfx;

METALCommandQueueImpl::METALCommandQueueImpl(METALDeviceImpl& device):
    _device(&device),
    _fence(device) 
{

}

void METALCommandQueueImpl::init(CommandQueueDesc& desc) {
    // ribe and create the command queue.
    //METAL_COMMAND_QUEUE_DESC queue = {};
    //queue.Flags = METAL_COMMAND_QUEUE_FLAG_NONE;
    //queue.Type = METAL_COMMAND_LIST_TYPE_DIRECT;

    //FenceBuilder f;
    //_fence.init(f.build());

    //getIMETALDevice().CreateCommandQueue(&queue, IID_IMETALCommandQueue, reinterpret_cast<vptr_t*>(&_queue));
}
    
void METALCommandQueueImpl::executeCommandList(ICommandList* lists, size_t count) {
    //auto f =  &reinterpret_cast<METALCommandListImpl*>(lists)->getIMETALCommandList();
    //_queue->ExecuteCommandLists(1, &f);

}

void METALCommandQueueImpl::flush() {
    //_fence.waitFor(_queue);
}