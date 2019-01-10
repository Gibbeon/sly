#include "sly/d3d12.h"
#include "sly/gfx.h"
#include "sly/d3d12/gfx/rendertarget.h"
#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/fence.h"
#include "sly/d3d12/gfx/descriptortable.h"

namespace sly {
    namespace os {
        class Win32Window;
    }

    namespace gfx {
        class D3D12CommandQueueImpl;

        class D3D12DeviceImpl;
        class D3D12WindowImpl : public IWindow {
        public:
            D3D12WindowImpl(D3D12DeviceImpl& device, sly::os::Win32Window& window);
            virtual void init(WindowDesc& desc);

            // window control
            virtual void setVisible(bool_t show);
            virtual void processMessages();

            // buffers
            virtual void swapBuffers();            
            IRenderTarget& getDrawBuffer() { return _renderTargets[_drawFrameIndex]; }       

            // draw
            virtual ICommandQueue& getDirectCommandQueue() { return _directCommandQueue; }

            virtual IDevice& getDevice() { return *_device; } 
            ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }

 
        private:
            IDXGISwapChain3* _swapChain;
            D3D12DeviceImpl* _device;     
            D3D12RenderTargetImpl _renderTargets[2];
            size_t _drawFrameIndex;
            
            sly::os::Win32Window* _window;

            D3D12FenceImpl _fence;
            D3D12CommandQueueImpl _directCommandQueue;
            D3D12DescriptorTableImpl _desctriptorTable;
        };
    }

}