#include "sly/metal.h"
#include "sly/gfx.h"
#include "sly/metal/gfx/rendertarget.h"
#include "sly/metal/gfx/commandqueue.h"
#include "sly/metal/gfx/fence.h"
#include "sly/metal/gfx/descriptortable.h"

namespace sly {
    namespace os {
        class MacOSWindow;
    }

    namespace gfx {
        class METALCommandQueueImpl;

        class METALDeviceImpl;
        class METALRenderContextImpl : public IRenderContext {
        public:
            METALRenderContextImpl(METALDeviceImpl& device, sly::os::MacOSWindow& window);
            virtual void init(RenderContextDesc& desc);

            // window control
            virtual void setVisible(bool_t show);
            virtual void processMessages();

            // buffers
            virtual void swapBuffers();            
            IRenderTarget& getDrawBuffer() { return _renderTargets[_drawFrameIndex]; }       

            // draw
            virtual ICommandQueue& getDirectCommandQueue() { return _directCommandQueue; }

            virtual IDevice& getDevice() { return *_device; } 
            //ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }

 
        private:
            //IDXGISwapChain3* _swapChain;
            METALDeviceImpl* _device;     
            METALRenderTargetImpl _renderTargets[2];
            size_t _drawFrameIndex;
            
            sly::os::MacOSWindow    * _window;

            METALFenceImpl _fence;
            METALCommandQueueImpl _directCommandQueue;
            METALDescriptorTableImpl _desctriptorTable;
        };
    }

}