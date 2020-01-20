#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/device.h"


namespace sly {
    namespace gfx {
        struct FenceDesc {

        };

        class FenceBuilder : public Builder<FenceDesc> {

        };

        class D3D12DeviceImpl;
        class D3D12FenceImpl {
        public:
            D3D12FenceImpl(D3D12DeviceImpl& device);
            
            virtual retval<void> init(const FenceDesc& desc = FenceBuilder().build());
            virtual retval<void> release();
            
            template <class TSignalClass>  
            void waitFor(TSignalClass& object, size_t timeout = INFINITE);
            
            void wait(size_t timeout = INFINITE);
            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            virtual IDevice& getDevice() { return *_device; } 
        

        private:
            D3D12DeviceImpl* _device;
            HANDLE _fenceEvent;
            ID3D12Fence* _fence;
            uint_t _fenceValue;
            bool_t _initialized;
        };

        template <class TSignalClass>            
        void D3D12FenceImpl::waitFor(TSignalClass& object, size_t timeout) {
            // Signal and increment the fence value.
            object->Signal(_fence, _fenceValue);
           
            // Wait until the previous frame is finished.
            if (_fence->GetCompletedValue() < _fenceValue)
            {
                // Wait until the fence is completed.
                _fence->SetEventOnCompletion(_fenceValue, _fenceEvent);
                WaitForSingleObject(_fenceEvent, (DWORD)timeout);
            }

             _fenceValue++;
        }            
    }
}

