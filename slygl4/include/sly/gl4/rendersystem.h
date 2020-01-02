#pragma once 

#include "sly/gl4.h"
#include "sly/gfx/rendersystem.h"
#include "sly/gfx/device.h"

namespace sly {
    namespace gfx {
        class GL4RenderSystemImpl : public IRenderSystem {
        public:
            GL4RenderSystemImpl();

            virtual retval<std::unique_ptr<IDevice>> createDevice(Device& desc);
        private:
        };
    }
}