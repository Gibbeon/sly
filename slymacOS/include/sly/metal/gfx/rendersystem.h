#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class METALRenderSystemImpl : public IRenderSystem {
            _GET_TYPE_INFO();

            virtual retval<std::unique_ptr<IDevice>> createDevice(DeviceDesc& desc);
        };  
    }
}