#pragma once

#include "sly/global.h"
#include "sly/io/iostream.h"

namespace sly {
    class MemoryStream : public IInputOutputStream {
    public:
        
        MemoryStream();
        MemoryStream(size_t length);
        virtual ~MemoryStream();
        
        virtual retval<size_t>  read(vptr_t buffer, size_t size);
        virtual retval<void>    write(vptr_t data, size_t size);

        virtual size_t size() const;
        virtual size_t position() const;
        
        virtual retval<void> seek(s64 offset);
        virtual retval<void> setPosition(size_t position);

        virtual retval<void> flush();
        virtual retval<void> close();

    protected:
        std::vector<byte_t> _buffer;
        size_t _position;
    }; 
}