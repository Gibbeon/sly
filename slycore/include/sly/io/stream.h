#pragma once

#include "sly/global.h"

namespace sly {
    class IStream {
    public:
        virtual ~IStream() {}

        virtual size_t getSize() = 0;
        
        virtual void seek(s32 offset) = 0;
        virtual size_t getPosition() = 0;
        virtual void setPosition(size_t position) = 0;

        virtual void flush() = 0;
        virtual void close() = 0;

        
    protected:
        IStream() {}
    }; 
}