#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"
#include "sly/gfx/commandqueue.h"
#include "sly/d3d12/gfx/fence.h"

namespace sly {
    namespace gfx {
        class ICommandList;
        class D3D12CommandQueueImpl : public ICommandQueue, public D3D12ManagedImpl {
        public:
            D3D12CommandQueueImpl(ref_t<D3D12DeviceImpl> device, ref_t<CommandQueueDesc> desc = DEFAULT);
            
            virtual void executeCommandList(ref_t<ICommandList> lists); // where is my render target
            
            ref_t<ID3D12CommandQueue> getID3D12CommandQueue() { return queue_; }
                    
        protected:
            //using D3D12ManagedImpl::D3D12ManagedImpl;

        private:
            ref_t<ID3D12CommandQueue> queue_;
            D3D12FenceImpl fence_;
        };
    }
}