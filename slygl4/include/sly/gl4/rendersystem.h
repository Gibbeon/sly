#pragma once 

#include "sly/gl4.h"
#include "sly/gfx/rendersystem.h"
#include "sly/gfx/device.h"

namespace sly {
    namespace gfx {
        class GL4RenderInterface : public IRenderInterface {
        public:
            GL4RenderInterface();

            virtual retval<std::unique_ptr<IDevice>> createDevice(Device& desc);
        private:
        };
    }
}