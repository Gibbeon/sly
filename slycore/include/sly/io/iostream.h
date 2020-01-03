#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/io/outputstream.h"

namespace sly {
    class IInputOutputStream : public IInputStream, public IOutputStream {
    public:
        virtual ~IInputOutputStream() {}

    protected:
        IInputOutputStream() {}
    }; 
}