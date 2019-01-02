#pragma once

#include "sly/d3d12.h"
#include "sly/gfx/commandqueue.h"
#include "sly/d3d12/gfx/fence.h"

namespace sly {
    namespace gfx {
        class ICommandList;
        class D3D12CommandQueueImpl : public ICommandQueue {
        public:
            D3D12CommandQueueImpl(D3D12DeviceImpl& device);
            virtual void init(CommandQueueDesc& desc);
            
            virtual void executeCommandList(ICommandList* lists, size_t count = 1); // where is my render target
            
            ID3D12CommandQueue& getID3D12CommandQueue() { return *_queue; }
            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            virtual IDevice& getDevice() { return *_device; } 

        private:
            ID3D12CommandQueue* _queue;
            D3D12DeviceImpl* _device; 

            D3D12FenceImpl _fence;
        };
    }
}