#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class METALRendererImpl : public IRenderer {
            _GET_TYPE_INFO();

            virtual std::string getName() { return "METALRenderer"; }

            virtual retval<void> onLoad() { GraphicSystem::addRenderer(this); return success(); }
            virtual retval<void> onUnload() { return success(); }

            virtual retval<std::unique_ptr<IDevice>> createDevice(DeviceDesc& desc);
        };  
    }
}