#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <fstream>

#include "sly/win32.h"
#include "sly/os/os.h"

namespace sly { 
namespace os {
    class Win32FileInputStream : public IInputStream {
    public:
                Win32FileInputStream() {}
        virtual ~Win32FileInputStream() {}

        virtual void open(const char_t* file);
        virtual size_t read(vptr_t buffer, size_t size);
        virtual size_t getSize();

        virtual void seek(size_t offset)  { _offset += offset; }
        virtual size_t getPosition()  { return _offset; }
        virtual void setPosition(size_t position)  { _offset = position; };

        virtual void flush() {}
        virtual void close();
    private:
        HANDLE _handle;
        vptr_t _file;
        size_t _size;
        size_t _offset;
    };

    class Win32FileOutputStream : public IOutputStream {
    public:        
        Win32FileOutputStream() {}
        virtual ~Win32FileOutputStream() {}

        virtual void open(const char_t* file);
        virtual void write(vptr_t buffer, size_t size);
        virtual void close();

        virtual size_t getSize();

        virtual void seek(size_t offset);
        virtual size_t getPosition();
        virtual void setPosition(size_t position);

        virtual void flush() {}
    protected:
        std::fstream _file;
    };

    class Win32FileSystem : public IFileSystem {
        virtual void open(IInputStream** ppStream, const char_t* file) {
            (*ppStream) = new Win32FileInputStream();
            reinterpret_cast<Win32FileOutputStream*>(*ppStream)->open(file);
        }

        virtual void create(IOutputStream** ppStream, const char_t* file) {
            (*ppStream) = new Win32FileOutputStream();
            reinterpret_cast<Win32FileOutputStream*>(*ppStream)->open(file);
        }
    };

    class Win32OperatingSystem : public IOperatingSystem {
    public:
        

        Win32OperatingSystem();
        virtual ~Win32OperatingSystem() {}

        virtual void init();
        virtual size_t getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max);

        virtual IFileSystem& FileSystem() { return _fs; }

    protected:

    private:
        Win32FileSystem _fs;
    };
}}