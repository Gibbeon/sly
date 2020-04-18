#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/fence.h"
#include "sly/gfx/commandqueue.h"

namespace sly {
    namespace gfx {
        class ICommandList;
        class D3D12CommandQueueImpl : public ICommandQueue {
        public:
            D3D12CommandQueueImpl(D3D12DeviceImpl& device);
            virtual retval<void>
                                 init(const CommandQueueDesc& desc = CommandQueueBuilder().build());
            virtual retval<void> release();

            virtual void executeCommandLists(
                gsl::span<ICommandList*> lists);   // where is my render target

            virtual void flush();

            ID3D12CommandQueue& getID3D12CommandQueue() { return *_queue; }
            ID3D12Device&       getID3D12Device() {
                return _device->getID3D12Device();
            }
            virtual IDevice& getDevice() { return *_device; }

        private:
            ID3D12CommandQueue* _queue;
            D3D12DeviceImpl*    _device;

            D3D12FenceImpl _fence;
        };
    }   // namespace gfx
}   // namespace sly