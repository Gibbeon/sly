#pragma once

#include <stdio.h>

#include <fstream>

#include "sly/macOS.h"
#include "sly/io/iostream.h"
#include "sly/os/operatingsystem.h"
#include "sly/os/filesystem.h"

namespace sly {
    namespace os {
    class MacOSFileStream : public IInputOutputStream {
    public:
                MacOSFileStream() {}
        virtual ~MacOSFileStream() {}

        virtual retval<void> open(const char_t* file);
        virtual void write(vptr_t buffer, size_t size) {}
        virtual size_t read(vptr_t buffer, size_t size);
        virtual size_t getSize();
        
        virtual void seek(s32 offset)  { _offset += offset; }
        virtual size_t getPosition()  { return _offset; }
        virtual void setPosition(size_t position)  { _offset = position; };

        virtual void flush() {}
        virtual void close();
    private:
        int _file;
        vptr_t _data;
        size_t _size;
        size_t _offset;
    };

    class MacOSFileSystem : public IFileSystem {
        virtual retval<void> init(FileSystemDesc&) { return success(); }

        virtual retval<std::unique_ptr<File>> open(const char_t* file) {
            auto stream = new MacOSFileStream();
            if(stream->open(file).failed()) {
                throw;
            }

            return std::make_unique<File>(stream);
        }

        //virtual void create(IOutputStream** ppStream, const char_t* file) {
        //    (*ppStream) = new MacOSFileOutputStream();
        //    reinterpret_cast<MacOSFileOutputStream*>(*ppStream)->open(file);
        //    
        //}
    };

    class MacOSSystemInterface : public ISystemInterface {
    public:
                MacOSSystemInterface();
        virtual ~MacOSSystemInterface() {}

        virtual retval<void> init(SystemInterfaceDesc&);
        
        virtual retval<vptr_t> loadLibrary(std::string) { return failed<vptr_t>(); }
        virtual retval<vptr_t> getProcAddress(std::string, vptr_t handle = nullptr) { return failed<vptr_t>(); }

        virtual retval<IFileSystem&> filesystem() { return _fs; }

    protected:

    private:
        MacOSFileSystem _fs;
    };
}}