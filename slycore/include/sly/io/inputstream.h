#pragma once

#include "sly/global.h"
#include "sly/io/stream.h"

namespace sly {
    class IInputStream : public virtual IStream {
    public:
        virtual ~IInputStream() {}

                
        virtual retval<size_t>  read(vptr_t buffer, size_t size) = 0;

    protected:
        IInputStream() : IStream() {}
    }; 
}