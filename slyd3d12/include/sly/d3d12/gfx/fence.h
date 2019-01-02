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
            D3D12FenceImpl(D3D12DeviceImpl& device);
            virtual void init(FenceDesc& desc);
            
            template <class TSignalClass>  
            void waitFor(TSignalClass& object, size_t timeout = INFINITE);
            
            void wait(size_t timeout = INFINITE);
        

        private:
            HANDLE _fenceEvent;
            ID3D12Fence* _fence;
            uint_t _fenceValue;
        };

        template <class TSignalClass>            
        void D3D12FenceImpl::waitFor(TSignalClass& object, size_t timeout) {
            // Signal and increment the fence value.
            object->Signal(_fence, _fenceValue);
            _fenceValue++;

            // Wait until the previous frame is finished.
            if (_fence->GetCompletedValue() < _fenceValue)
            {
                // Wait until the fence is completed.
                _fence->SetEventOnCompletion(_fenceValue, _fenceEvent);
                WaitForSingleObject(_fenceEvent, timeout);
            }
        }
            
    }
}

