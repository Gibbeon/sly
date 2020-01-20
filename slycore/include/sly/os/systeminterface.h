#pragma once

#include "sly/global.h"
#include "sly/os/builders/operatingsystembuilder.h"

namespace sly {
    class Kernel;
    namespace os {
        class IFileSystem;
        class IWindowSystem;
        class ISystemInterface {
        public:            
            typedef vptr_t SystemHandle;

            virtual ~ISystemInterface() {}  
                      
            virtual retval<void> init() = 0;
            virtual retval<void> release() = 0;

            virtual retval<SystemHandle> loadLibrary(gsl::czstring_span<>) = 0;
            virtual retval<SystemHandle> getProcAddress(gsl::czstring_span<>, SystemHandle handle = nullptr) = 0;
                        
            virtual IFileSystem& filesystem() const = 0;
            virtual IWindowSystem& windows() const = 0;
            
        protected:
            ISystemInterface() {}
        };   

        extern ISystemInterface* GetSystemInterface(sly::Kernel& kernel);  
    }
}
