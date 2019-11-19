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
            
            mtlpp::CommandQueue& getMETALCommandQueue() { return _queue; }
            mtlpp::Device& getMETALDevice()   { return _device.getMETALDevice(); }

            virtual IDevice& getDevice() { return _device; } 

        private:
            mtlpp::CommandQueue _queue;
            METALDeviceImpl& _device; 

            //METALFenceImpl _fence;
        };
    }
}