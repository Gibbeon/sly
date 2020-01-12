#pragma once

#include "sly/global.h"
#include "sly/runtime/typeinfo.h"
#include "sly/runtime/serialization/serializer.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly { 
    class ISerializable : public virtual IHasTypeInfo {
    public:
        virtual ~ISerializable() {}
        

        //virtual gsl::czstring<> getType() const = 0;
        //virtual gsl::czstring<> getName() const = 0;

        virtual retval<void> serialize(ISerializer& archive) = 0;
        virtual retval<void> deserialize(IDeserializer& archive) = 0;
    
    protected:
        ISerializable() {}
    };
}



