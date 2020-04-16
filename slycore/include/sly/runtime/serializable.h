#pragma once

#include "sly/global.h"
#include "sly/runtime/typeinfo.h"
#include "sly/runtime/serialization/serializer.h"
#include "sly/runtime/serialization/deserializer.h"

#define READ_PROPERTY_3(x, y, z)   archive.property( x ).read( y , z );
#define READ_PROPERTY_2(x, y)      archive.property( #x ).read( x , y );
#define READ_PROPERTY_1(x)         archive.property( #x ).read( x );
#define READ_PROPERTY_0() __halt()

#define FUNC_CHOOSER(_f1, _f2, _f3, _f4, ...) _f4
#define FUNC_RECOMPOSER(argsWithParentheses) FUNC_CHOOSER argsWithParentheses
#define CHOOSE_FROM_ARG_COUNT(...) FUNC_RECOMPOSER((__VA_ARGS__, READ_PROPERTY_3, READ_PROPERTY_2, READ_PROPERTY_1, ))
#define NO_ARG_EXPANDER() ,,READ_PROPERTY_0
#define MACRO_CHOOSER(...) CHOOSE_FROM_ARG_COUNT(NO_ARG_EXPANDER __VA_ARGS__ ())

#define DESERIALIZE(...) MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

namespace sly { 
    class ISerializable : public virtual IHasTypeInfo {
    public:
        virtual ~ISerializable() {}

        virtual retval<void> serialize(ISerializer& archive) = 0;
        virtual retval<void> deserialize(IDeserializer& archive) = 0;
    
    protected:
        ISerializable() {}
    };
}



