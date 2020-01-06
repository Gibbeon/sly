#pragma once

#include "sly/global.h"
#include "sly/os/systeminterface.h"
#include "sly/os/builders/operatingsystembuilder.h"

namespace sly {
    namespace os {
        class IFileSystem;
        class ISystemInterface;

        class IOperatingSystem {
        public:
            typedef vptr_t SystemHandle;

            virtual ~IOperatingSystem() {} 

            virtual retval<void> init() = 0;
            virtual retval<void> release() = 0;

            virtual retval<SystemHandle> loadLibrary(gsl::czstring_span<>) = 0;
            virtual retval<SystemHandle> getProcAddress(gsl::czstring_span<>, SystemHandle handle = nullptr) = 0;
            
            virtual IFileSystem&        filesystem() const = 0;
            virtual IWindowSystem&      windows() const = 0;
            
        protected:
            IOperatingSystem() {}

        };   

        class OperatingSystem : public IOperatingSystem {
        public: 
            OperatingSystem(sly::Kernel& kernel);          
            virtual ~OperatingSystem();  

            virtual retval<void> init();
            virtual retval<void> release();

            virtual retval<SystemHandle> loadLibrary(gsl::czstring_span<>);
            virtual retval<SystemHandle> getProcAddress(gsl::czstring_span<>, SystemHandle handle = nullptr);
            
            virtual IFileSystem&         filesystem() const;
            virtual IWindowSystem&       windows() const;
            
        protected:
            sly::Kernel& _kernel;
            ISystemInterface* _system;
        };   

        extern ISystemInterface* GetSystemInterface();  
    }
}
