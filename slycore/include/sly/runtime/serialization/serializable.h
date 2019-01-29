#pragma once

#include "sly/global.h"
#include "sly/io/istream.h"
#include "sly/io/ostream.h"
#include "sly/runtime/hastypeinfo.h"

namespace sly {
    class ISerializer;
    class IDeserializer;
    class ISerializable : public IHasTypeInfo {
    public:
        virtual ~ISerializable() {}
            
        virtual void serialize(ISerializer&) = 0;
        virtual void deserialize(IDeserializer&) = 0;

    protected:
        ISerializable() {}    
    };
}