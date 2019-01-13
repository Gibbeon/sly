#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class D3D12RenderSystemImpl : public IRenderSystem {
            _GET_TYPE_INFO();

            virtual void createDevice(IDevice** outDevice, DeviceDesc& desc);
        };  
    }
}