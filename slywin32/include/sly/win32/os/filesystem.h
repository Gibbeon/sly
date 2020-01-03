#pragma once

#include "sly/win32.h"
#include "sly/os/filesystem.h"
#include "sly/win32/os/filestream.h"

namespace sly { 
namespace os {
 
    class Win32FileSystem : public IFileSystem {
        virtual retval<void> init(FileSystemDesc&) { return success(); }

        virtual retval<std::unique_ptr<File>> open(const char_t* file) {
            
            auto stream = new Win32FileStream();
            if(stream->open(file).failed()) {
                throw;
            }

            return std::make_unique<File>(stream);
        }

        //virtual void create(IOutputStream** ppStream, const char_t* file) {
        //    (*ppStream) = new Win32FileOutputStream();
        //    reinterpret_cast<Win32FileOutputStream*>(*ppStream)->open(file);
       // }
    };    
}}