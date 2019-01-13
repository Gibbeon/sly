#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <fstream>

#include "sly/win32.h"
#include "sly/os/os.h"

namespace sly {
    class Win32FileInputStream : public IFileInputStream {
    public:
                Win32FileInputStream() {}
        virtual ~Win32FileInputStream() {}

        virtual void open(const char_t* file);
        virtual void read(vptr_t buffer, size_t size);
        virtual size_t getSize();
        
        virtual void close();
    private:
        HANDLE _handle;
        vptr_t _file;
        size_t _size;
    };

    class Win32FileOutputStream : public IFileOutputStream {
    public:        
        Win32FileOutputStream() {}
        virtual ~Win32FileOutputStream() {}

        virtual void open(const char_t* file);
        virtual void write(vptr_t buffer, size_t size);
        virtual void close();
    protected:
        std::fstream _file;
    };

    class Win32FileSystem : public IFileSystem {
        virtual void open(IFileInputStream** ppStream, const char_t* file) {
            (*ppStream) = new Win32FileInputStream();
            (*ppStream)->open(file);
        }

        virtual void create(IFileOutputStream** ppStream, const char_t* file) {
            (*ppStream) = new Win32FileOutputStream();
            (*ppStream)->open(file);
        }
    };

    class Win32OperatingSystem : public IOperatingSystem {
    public:
        Win32OperatingSystem();
        virtual ~Win32OperatingSystem() {}

        virtual void init();

        virtual IFileSystem& FileSystem() { return _fs; }

    protected:
        void loadModules();

    private:
        Win32FileSystem _fs;
    };
}