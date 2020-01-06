#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <fstream>

#include "sly/win32.h"
#include "sly/io/iostream.h"
#include "sly/os/operatingsystem.h"

namespace sly { 
namespace os {
    class Win32FileStream : public IInputOutputStream {
    public:
                Win32FileStream() : IInputOutputStream() {}
        virtual ~Win32FileStream() {}

        virtual retval<void> open(gsl::zstring<> file);
        virtual size_t read(vptr_t buffer, size_t size);
        virtual void write(vptr_t buffer, size_t size) {}
        virtual size_t getSize();

        virtual void seek(s32 offset) { _offset += offset; }

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
}}