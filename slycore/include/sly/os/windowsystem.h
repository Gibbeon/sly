#pragma once

#include "sly/global.h"
#include "sly/os/window.h"

namespace sly {
    namespace os {
        class IWindowSystem {
        public:
            virtual ~IWindowSystem() {}
            
            virtual retval<void> init() = 0;
            virtual retval<void> release() = 0;

            virtual retval<std::shared_ptr<IWindow>> create(const WindowDesc& desc = WindowBuilder().build()) = 0;

            virtual gsl::span<const std::shared_ptr<IWindow>>  windows() const = 0;
            virtual retval<void> release(IWindow& window) = 0;
            
        protected:
            IWindowSystem() {}
        };
    }
}