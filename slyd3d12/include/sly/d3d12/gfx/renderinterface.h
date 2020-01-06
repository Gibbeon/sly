#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        class D3D12RenderInterface : public IRenderInterface {
        public:
            D3D12RenderInterface(sly::Kernel& kernel);
            virtual ~D3D12RenderInterface();

            virtual retval<void> init();
            virtual retval<void> release();

            virtual sly::retval<std::unique_ptr<IDevice>> createDevice(const DeviceDesc& desc);

        private:
            sly::Kernel& _kernel;
        };  
    }
}