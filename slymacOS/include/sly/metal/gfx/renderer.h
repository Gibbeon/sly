#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class METALRenderInterface : public IRenderInterface {
            _GET_TYPE_INFO();

            virtual std::string getName() { return "METALRenderer"; }

            virtual retval<std::unique_ptr<IDevice>> createDevice(DeviceDesc& desc);
        };  
    }
}