#pragma once

#include "sly/metal.h"
#include "sly/metal/gfx/device.h"


namespace sly {
    namespace gfx {
        struct FenceDesc {

        };

        class FenceBuilder : public Builder<FenceDesc> {

        };

        class METALDeviceImpl;
        class METALFenceImpl {
        public:
            METALFenceImpl(METALDeviceImpl& device);
            virtual void init(FenceDesc& desc);
            
            template <class TSignalClass>  
            void waitFor(TSignalClass& object, size_t timeout = INFINITE);
            
            void wait(size_t timeout = INFINITE);
            //ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            virtual IDevice& getDevice() { return *_device; } 
        

        private:
            METALDeviceImpl* _device;
            //HANDLE _fenceEvent;
            //ID3D12Fence* _fence;
            uint_t _fenceValue;
        };

        template <class TSignalClass>            
        void METALFenceImpl::waitFor(TSignalClass& object, size_t timeout) {
            /*// Signal and increment the fence value.
            object->Signal(_fence, _fenceValue);
           
            // Wait until the previous frame is finished.
            if (_fence->GetCompletedValue() < _fenceValue)
            {
                // Wait until the fence is completed.
                _fence->SetEventOnCompletion(_fenceValue, _fenceEvent);
                WaitForSingleObject(_fenceEvent, (DWORD)timeout);
            }

             _fenceValue++;
             */
        }            
    }
}

