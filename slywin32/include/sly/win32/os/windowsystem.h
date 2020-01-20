#pragma once

#include "sly/global.h"
#include "sly/os/windowsystem.h"

namespace sly {
    class Kernel;
    namespace os {
        class Win32WindowSystem : public IWindowSystem {
        public:            
            Win32WindowSystem(Kernel& kernel);
            virtual ~Win32WindowSystem();
            
            virtual retval<void> init();
            virtual retval<void> release();

            virtual retval<std::shared_ptr<IWindow>> create(const WindowDesc& desc = WindowBuilder().build());

            virtual gsl::span<const std::shared_ptr<IWindow>> windows() const;
            virtual retval<void> release(IWindow& window);
            
        private:
            Kernel& _kernel;
            std::vector<std::shared_ptr<IWindow>> _windows;
        };
    }
}