#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace os {

         struct FileSystemDesc 
        {
            
        };

        class FileSystemBuilder : public sly::Builder<FileSystemDesc>
        {
        public:
            FileSystemBuilder() : Builder() {}
            virtual ~FileSystemBuilder() {}
        };

    }
}