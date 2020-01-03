#pragma once

#include "sly/global.h"
#include "sly/os/builders/operatingsystembuilder.h"

namespace sly {
    namespace os {
        class IFileSystem;

        class IOperatingSystem {
        public:
            virtual ~IOperatingSystem() {}            
            virtual retval<void> init(OperatingSystemDesc&) = 0;
            
            virtual retval<vptr_t> loadLibrary(std::string) = 0;
            virtual retval<vptr_t> getProcAddress(std::string, vptr_t handle = nullptr) = 0;
            
            virtual retval<IFileSystem&> filesystem() = 0;
            
        protected:
            IOperatingSystem() {}
        };   

        extern IOperatingSystem* _GetOperatingSystem();
        
        class OperatingSystem : IOperatingSystem{
        public:
        
            OperatingSystem() {}
            virtual ~OperatingSystem() {}            
            virtual retval<void> init(OperatingSystemDesc&); 
            
            virtual retval<vptr_t> loadLibrary(std::string moniker)  { return _impl->loadLibrary(moniker); }
            virtual retval<vptr_t> getProcAddress(std::string moniker, vptr_t handle = nullptr) { return _impl->getProcAddress(moniker, handle); }
            
            virtual retval<IFileSystem&> filesystem() { return _impl->filesystem(); }
            
        protected:
            IOperatingSystem* _impl;
        };   
    }
}
