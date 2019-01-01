#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"

namespace sly {
    namespace gfx {
        struct FenceDesc {

        };

        class FenceDescBuilder : public Builder<FenceDesc> {

        };

        class D3D12DeviceImpl;
        class D3D12FenceImpl : public D3D12ManagedImpl {
        public:
            D3D12FenceImpl(ref_t<D3D12DeviceImpl> device, ref_t<FenceDesc> = DEFAULT);
            
            template <class TSignalClass>  
            void waitFor(ref_t<TSignalClass> object, size_t timeout = INFINITE);
            
            void wait(size_t timeout = INFINITE);
        
        protected:
            constexpr static FenceDesc DEFAULT = { /* capacity */ };  

        private:
            HANDLE fenceEvent_;
            ref_t<ID3D12Fence> fence_;
            uint_t fenceValue_;
        };

        template <class TSignalClass>            
        void D3D12FenceImpl::waitFor(ref_t<TSignalClass> object, size_t timeout) {
            // Signal and increment the fence value.
            object->Signal(fence_, fenceValue_);
            fenceValue_++;

            // Wait until the previous frame is finished.
            if (fence_->GetCompletedValue() < fenceValue_)
            {
                // Wait until the fence is completed.
                fence_->SetEventOnCompletion(fenceValue_, fenceEvent_);
                WaitForSingleObject(fenceEvent_, timeout);
            }
        }
            
    }
}

