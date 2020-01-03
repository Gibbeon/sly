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
    }
}