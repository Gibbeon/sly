#pragma once

#include "sly/metal.h"
#include "sly/gfx/commandqueue.h"
#include "sly/metal/gfx/fence.h"

namespace sly {
    namespace gfx {
        class ICommandList;
        class METALCommandQueueImpl : public ICommandQueue {
        public:
            METALCommandQueueImpl(METALDeviceImpl& device);
            virtual void init(CommandQueueDesc& desc);
            
            virtual void executeCommandList(ICommandList* lists, size_t count = 1); // where is my render target

            virtual void flush();
            
            //ID3D12CommandQueue& getID3D12CommandQueue() { return *_queue; }
            //ID3D12Device& getID3D12Device()   { return _device->getIMETALDevice(); }
            virtual IDevice& getDevice() { return *_device; } 

        private:
            //ID3D12CommandQueue* _queue;
            METALDeviceImpl* _device; 

            METALFenceImpl _fence;
        };
    }
}