#pragma once

#include "sly/global.h"
#include "sly/io/iostream.h"

namespace sly {
    class MemoryStream : public IInputOutputStream {
    public:
        MemoryStream(std::shared_ptr<void> buffer, size_t length);
        virtual ~MemoryStream() {}
        
        virtual size_t read(vptr_t buffer, size_t size) = 0;
        virtual void write(vptr_t data, size_t size) = 0;

        virtual size_t getSize() = 0;
        
        virtual void seek(size_t offset) = 0;
        virtual size_t getPosition() = 0;
        virtual void setPosition(size_t position) = 0;

        virtual void flush() = 0;
        virtual void close() = 0;

    protected:
        std::shared_ptr<void> _buffer;
        size_t _position;
        size_t _length;
    }; 
}