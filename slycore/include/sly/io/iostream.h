#pragma once

#include "sly/global.h"
#include "sly/io/istream.h"
#include "sly/io/ostream.h"

namespace sly {
    class IInputOutputStream : public IInputStream, public IOutputStream {
    public:
        virtual ~IInputOutputStream() {}

    protected:
        IInputOutputStream() {}
    }; 
}