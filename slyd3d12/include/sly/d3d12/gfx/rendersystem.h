#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class D3D12RenderSystemImpl : public IRenderSystem {
            virtual const TypeInfo& getType() {
                static const TypeInfo instance = TypeInfo::get<decltype(*this)>();
                return instance;
            }

            virtual void createDevice(IDevice** outDevice, DeviceDesc& desc);
        };  
    }
}