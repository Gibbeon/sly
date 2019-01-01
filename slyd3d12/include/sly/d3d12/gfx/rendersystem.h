#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class D3D12RenderSystemImpl : public IRenderSystem {
            virtual void createDevice(out_ptr_t<IDevice> outDevice, ref_t<DeviceDesc> desc = IDevice::DEFAULT_DESC);
        };  
    }
}