#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class D3D12RendererImpl : public IRenderer {
        public:
            _GET_TYPE_INFO();

            virtual sly::retval<std::unique_ptr<IDevice>> createDevice(DeviceDesc& desc);

            virtual std::string getName() { return "D3D12Renderer"; }

            virtual retval<void> onLoad() { GraphicSystem::addRenderer(this); return success(); }
            virtual retval<void> onUnload() { return success(); }
        };  
    }
}