#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class METALRendererImpl : public IRenderer {
            _GET_TYPE_INFO();

            virtual retval<std::unique_ptr<IDevice>> createDevice(DeviceDesc& desc);
        };  
    }
}