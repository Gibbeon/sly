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
    class IFileStream : public virtual IInputOutputStream {
    public:
        virtual ~IFileStream() {}

        virtual retval<void> open(gsl::czstring<> file) = 0;

    protected:
        IFileStream() {}

    };

    class Win32FileStream : public IFileStream {
    public:
                Win32FileStream() : IFileStream() {}
        virtual ~Win32FileStream() {}

        virtual retval<void> open(gsl::czstring<> file);

        virtual retval<size_t> read(vptr_t buffer, size_t size);
        virtual retval<void> write(vptr_t buffer, size_t size) { return failed(); }
        virtual size_t size() const;

        virtual retval<void> seek(s64 offset) { _offset += offset;  return success();  }

        virtual size_t position() const  { return _offset; }
        virtual retval<void> setPosition(size_t position)  { _offset = position;  return success(); };

        virtual retval<void> flush() { return success(); }
        virtual retval<void> close();
    private:
        HANDLE _handle;
        vptr_t _file;
        size_t _size;
        size_t _offset;        
    };
}}