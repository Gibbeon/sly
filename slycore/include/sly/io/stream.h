#pragma once

#include "sly/global.h"

namespace sly {
    class IStream {
    public:
        virtual ~IStream() {}


        virtual size_t size() const = 0;
        virtual size_t position() const = 0;

        virtual retval<void> seek(s64 offset) = 0;
        virtual retval<void> setPosition(size_t position) = 0;

        virtual retval<void> flush() = 0;
        virtual retval<void> close() = 0;
        
    protected:
        IStream() {}
    }; 
}