#pragma once

#include "sly/global.h"
#include "sly/io/stream.h"

namespace sly {

    class IOutputStream : public virtual IStream {
    public:
        virtual ~IOutputStream() {}

        virtual retval<void>    write(vptr_t data, size_t size) = 0;

    protected:
        IOutputStream() {}
    }; 
}
