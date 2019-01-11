#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/runtime/serialization/serializable.h"

namespace sly {
    class IDeserializer {
    public:
        virtual ~IDeserializer() {}
        virtual ISerializable* read(IIStream&, IHeap&) = 0;
    protected:
        IDeserializer() {}
    };
}