#pragma once

#include <stdio.h>

#include <fstream>

#include "sly/macOS.h"
#include "sly/os/os.h"

namespace sly {
    namespace os {
    class MacOSFileInputStream : public IInputStream {
    public:
                MacOSFileInputStream() {}
        virtual ~MacOSFileInputStream() {}

        virtual void open(const char_t* file);
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

    class MacOSFileOutputStream : public IOutputStream {
    public:        
        MacOSFileOutputStream() {}
        virtual ~MacOSFileOutputStream() {}

        virtual void open(const char_t* file);
        virtual void write(vptr_t buffer, size_t size);
        virtual void close();

        virtual size_t getSize();

        virtual void seek(s32 offset);
        virtual size_t getPosition();
        virtual void setPosition(size_t position);

        virtual void flush() {}
    protected:
        std::fstream _file;
    };

    class MacOSFileSystem : public IFileSystem {
        virtual void open(IInputStream** ppStream, const char_t* file) {
            (*ppStream) = new MacOSFileInputStream();
            reinterpret_cast<MacOSFileInputStream*>(*ppStream)->open(file);
            //(*ppStream)->open(file);
        }

        virtual void create(IOutputStream** ppStream, const char_t* file) {
            (*ppStream) = new MacOSFileOutputStream();
            reinterpret_cast<MacOSFileOutputStream*>(*ppStream)->open(file);
            
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
}}