#include "sly/global.h"
#include "sly/platform.h"
#include "sly/gfx.h"
#include "sly/d3d12.h"

namespace sly {
    namespace gfx {
        class D3D12RenderSystem : public IRenderSystem {
        public:
            void createDevice(out_ptr_t<IDevice> ppDevice, ref_t<DeviceDesc> desc) {}
        };
    }
}

extern "C" __declspec( dllexport ) void _CreateRenderSystemImpl(out_ptr_t<sly::gfx::IRenderSystem> ppRenderSystem, ref_t<sly::gfx::RenderSystemDesc> desc) {
    ppRenderSystem = new sly::gfx::D3D12RenderSystem();
};
