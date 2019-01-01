#include "sly/d3d12.h"
#include "sly/gfx.h"
#include "sly/d3d12/gfx/rendertarget.h"
#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/managed.h"
#include "sly/d3d12/gfx/fence.h"
#include "sly/d3d12/gfx/descriptortable.h"
#include "sly/collections/list.h"

namespace sly {
    namespace sys {
        class Win32Window;
    }

    namespace gfx {
        class D3D12CommandQueueImpl;

        class D3D12DeviceImpl;
        class D3D12WindowImpl : public D3D12ManagedImpl, public IWindow {
        public:
            D3D12WindowImpl(ref_t<D3D12DeviceImpl> device, ref_t<sly::sys::Win32Window> window);
            virtual void init(ref_t<WindowDesc> desc = IWindow::DEFAULT_DESC);

            // window control
            virtual void setVisible(bool_t show);
            virtual void processMessages();

            // buffers
            virtual void swapBuffers();            
            ref_t<IRenderTarget> getBackBuffer() { return &renderTargets_[drawFrameIndex_]; }       

            // draw
            virtual ref_t<ICommandQueue> getDirectCommandQueue() { return directCommandQueue_; }
 
        private:
            ref_t<IDXGISwapChain3> swapChain_;
            D3D12RenderTargetImpl renderTargets_[2];
            size_t drawFrameIndex_;
            
            ref_t<sly::sys::Win32Window> window_;

            D3D12FenceImpl fence_;
            D3D12CommandQueueImpl directCommandQueue_;
            D3D12DescriptorTableImpl desctriptorTable_;
        };
    }

}