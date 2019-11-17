#pragma once

#include "sly/global.h"
#include "sly/io/stream.h"

namespace sly {

    class IOutputStream : public IStream {
    public:
        virtual ~IOutputStream() {}

        virtual void write(const vptr_t data, size_t size) = 0;

    protected:
        IOutputStream() {}
    }; 
}
