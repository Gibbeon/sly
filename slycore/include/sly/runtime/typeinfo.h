#pragma once

#include <typeinfo>
#include <string>

#include "sly/static_hash.h"

typedef u32 type_id;

namespace sly {
    struct TypeInfo {
        TypeInfo( const char* typeName) :
            name(typeName),
            id(static_hash(typeName))
        {
        }
        
        type_id id; 
        const char* name;

        template <typename T>
        static const TypeInfo get() {
            return TypeInfo(typeid(T).name());
        }
        
        operator type_id() const { return this->id; }
        operator const char*() const { return this->name; }
    };
}
    
    /* struct TypeInfoData
    {
        TypeInfoData()
        :   typeIdCounter(0)
        {

        }

        static TypeInfoData& instance() {
            static TypeInfoData _internal;
            return _internal;
        }

        template<typename T>
        TypeInfo registerType() {
            typeNames[result] = TOSTRING(T);
            //ctors[result]= [] () { return reinterpret_cast<vptr_t>(new T()); };

            return TypeInfo(typeNames[result], result, ctors[result]);
        };

        type_id                 typeIdCounter;
        std::string             typeNames[MAX_TYPE_COUNT];
        std::function<vptr_t()> ctors[MAX_TYPE_COUNT];
    };

    template<typename T>                                                                          
    struct MetaTypeInfo                                                       
    {                                                                                       
        static const TypeInfo& getType()                                                        
        {                                                                                   
            static const TypeInfo result = TypeInfoData::instance().registerType<T>();                    
            return result;                                                                  
        }                                                                                   
    };  
}

#define REGISTER_TYPEID(T)                                                                      \
namespace sly                                                                                   \
{                                                                                               \
    template<>                                                                                  \
    struct MetaTypeInfo< T >                                                                    \
    {                                                                                           \
        static const TypeInfo& getType()                                                      \
        {                                                                                       \
            static const TypeInfo result = TypeInfoData::instance().registerType<T>();          \
            return result;                                                                      \
        }                                                                                       \
    };                                                                                          \
}

#define REGISTER_CLASS_TYPEID(T)                                                                \
namespace sly                                                                                   \
{                                                                                               \
    class T;                                                                                    \
}                                                                                               \
REGISTER_TYPEID(T)  

#define REGISTER_STRUCT_TYPEID(T)                                                               \
namespace sly                                                                                   \
{                                                                                               \
    struct T;                                                                                   \
}                                                                                               \
REGISTER_TYPEID(T)  
 */