#pragma once

#include <typeinfo>
#include <type_traits>
#include <string>
#include <functional>

#include "sly/static_hash.h"
typedef u32 type_id;

namespace sly {
    class ISerializable;
    class TypeInfo {
    public:
        TypeInfo(   const char* typeName, 
                    size_t byteSize, 
                    std::function<vptr_t(vptr_t)> ctor, 
                    bool_t isSerializable,
                    bool_t isPolymophic,
                    bool_t isArray,
                    const TypeInfo& arrayType) :
            _name(typeName),
            _id(static_hash(typeName)),
            _isPolymophic(isPolymophic),
            _size(byteSize),
            _ctor(ctor),
            _isSerializable(isSerializable),
            _isArray(isArray),
            _arrayType(&arrayType)
        {
        }
        
        template <typename T>
        static const TypeInfo get() {
            return TypeInfo(typeid(T).name(), 
                sizeof(T), 
                TypeInfo::buildConstructor<T>(),
                std::is_convertible<T*, sly::ISerializable*>::value,
                std::is_polymorphic<T>::value,
                std::is_array<T>::value,
                TypeInfo::getArrayType<T>()
                );
        }
       
        inline const char* getName() const { return _name; }
        inline size_t getSize() const { return _size; }
        inline type_id getId() const { return _id; }
        inline bool_t isPolymophic() const { return _isPolymophic; }
        inline bool_t isSerializable() const { return _isSerializable; }
        inline const TypeInfo& getArrayType() const { return *_arrayType; }
        inline bool_t isArray() const { return _isArray; }
        inline std::function<vptr_t(vptr_t)> const getDefaultConstructor() { return _ctor; }
        
        operator type_id() const { return this->_id; }
        operator const char*() const { return this->_name; }
    protected:
        type_id _id; 
        size_t _size;
        const char* _name;
        bool_t _isSerializable;
        bool_t _isPolymophic;
        bool_t _isArray;
        const TypeInfo* _arrayType;

        std::function<vptr_t(vptr_t)> _ctor;

        template <typename T>
        static const std::function<vptr_t(vptr_t)> buildConstructor() {
            static const std::function<vptr_t(vptr_t)> ctor = std::is_abstract<T>::value ? (std::function<vptr_t(vptr_t)>)[](vptr_t buffer) { return (vptr_t)nullptr; } : (std::function<vptr_t(vptr_t)>)[](vptr_t buffer) { return reinterpret_cast<vptr_t>(new (buffer) std::conditional<std::is_abstract<T>::value, u8, T>::type()); };
            return ctor;
        } 
        
        template <typename T>
        static const TypeInfo& getArrayType() {
            static const TypeInfo arrayInfo = std::is_array<T>::value ? get<std::remove_extent<T>::type>() : TypeInfo();
            return arrayInfo;
        }

        TypeInfo() :
            _name("void"),
            _id(static_hash("void")),
            _isPolymophic(false),
            _size(0),
            _ctor(nullptr),
            _isSerializable(false),
            _isArray(false),
            _arrayType(nullptr) {
        }
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