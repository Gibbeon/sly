#pragma once

#include "sly/global.h"
#include "sly/os/builders/filesystembuilder.h"
#include "sly/os/file.h"

namespace sly {
    namespace os {
        class IFileSystem {
        public:
            virtual ~IFileSystem() {}

            virtual retval<void> init(const FileSystemDesc&) = 0;
            virtual retval<void> release() = 0;

            virtual retval<File> open(gsl::zstring<> file) = 0;
            //virtual retval<std::unique_ptr<IFileStream>> create(const char_t* file) = 0;

        protected:
            IFileSystem() {}

        };       
    }
}