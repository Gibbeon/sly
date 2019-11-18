#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class METALRenderSystemImpl : public IRenderSystem {
            _GET_TYPE_INFO();

            virtual void createDevice(IDevice** outDevice, DeviceDesc& desc);
        };  
    }
}