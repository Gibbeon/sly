#pragma once

#include <stdio.h>

#include <fstream>

#include "sly/macOS.h"
#include "sly/os/os.h"

namespace sly {
    class MacOSFileInputStream : public IFileInputStream {
    public:
                MacOSFileInputStream() {}
        virtual ~MacOSFileInputStream() {}

        virtual void open(const char_t* file);
        virtual void read(vptr_t buffer, size_t size);
        virtual size_t getSize();
        
        virtual void close();
    private:
        vptr_t _file;
        size_t _size;
    };

    class MacOSFileOutputStream : public IFileOutputStream {
    public:        
        MacOSFileOutputStream() {}
        virtual ~MacOSFileOutputStream() {}

        virtual void open(const char_t* file);
        virtual void write(vptr_t buffer, size_t size);
        virtual void close();
    protected:
        std::fstream _file;
    };

    class MacOSFileSystem : public IFileSystem {
        virtual void open(IFileInputStream** ppStream, const char_t* file) {
            (*ppStream) = new MacOSFileInputStream();
            (*ppStream)->open(file);
        }

        virtual void create(IFileOutputStream** ppStream, const char_t* file) {
            (*ppStream) = new MacOSFileOutputStream();
            (*ppStream)->open(file);
        }
    };

    class MacOSOperatingSystem : public IOperatingSystem {
    public:
        

        MacOSOperatingSystem();
        virtual ~MacOSOperatingSystem() {}

        virtual void init();
        virtual size_t getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max);

        virtual IFileSystem& FileSystem() { return _fs; }

    protected:

    private:
        MacOSFileSystem _fs;
    };
}