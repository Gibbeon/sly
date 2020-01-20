#pragma once

#include "sly/win32.h"
#include "sly/os/filesystem.h"

namespace sly { 
    class Kernel;
    namespace os {
 
        class Win32FileSystem : public IFileSystem {
        public:
            Win32FileSystem(sly::Kernel& kernel);
            virtual ~Win32FileSystem();

            virtual retval<void> init(const FileSystemDesc& desc = FileSystemBuilder().build());
            virtual retval<void> release();

            virtual retval<File> open(gsl::czstring<> file);
        private:
            sly::Kernel& _kernel;
        };    
    }
}
