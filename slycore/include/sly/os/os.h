#pragma once

#include "sly/global.h"

namespace sly {
    class IFileInputStream {
    public:
        virtual ~IFileInputStream() {}
        virtual void open(const char_t* file) = 0;

        virtual void read(vptr_t buffer, size_t size) = 0;
        virtual size_t getSize() = 0;
        
        virtual void close() = 0;
    protected:
        IFileInputStream() {}
    };

    class IFileOutputStream {
    public:
        virtual ~IFileOutputStream() {}
        virtual void open(const char_t* file) = 0;

        virtual void write(vptr_t buffer, size_t size) = 0;
        
        virtual void close() = 0;
    protected:
        IFileOutputStream() {}
    };

    
    class IFileSystem {
    public:
        virtual ~IFileSystem() {}
        virtual void open(IFileInputStream** ppStream, const char_t* file) = 0;
        virtual void create(IFileOutputStream** ppStream, const char_t* file) = 0;
    protected:
        IFileSystem() {}

    };

    class IOperatingSystem {
    public:
        virtual ~IOperatingSystem() {}

        virtual void init() = 0;

        virtual IFileSystem& FileSystem() = 0;
    protected:
        IOperatingSystem() {}
    };
    
}