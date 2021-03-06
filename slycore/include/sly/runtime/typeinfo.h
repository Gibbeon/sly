#pragma once

#include <typeinfo>
#include <type_traits>
#include <string>
#include <functional>

#include "sly/static_hash.h"
typedef u32 type_id;

namespace sly {
    template <typename T, typename = typename std::is_enum<T>::type>
    struct safe_underlying_type {
        using type = int;
    };

    template <typename T>
    struct safe_underlying_type<T, std::true_type> {
        using type = std::underlying_type_t<T>; 
    };

    class ISerializable;
    class TypeInfo {
    public:
        TypeInfo(   const char* typeName, 
                    size_t byteSize, 
                    std::function<vptr_t(vptr_t)> ctor, 
                    bool_t isSerializable,
                    bool_t isPolymophic,
                    bool_t isArray,
                    bool_t isEnum,
                    const TypeInfo& underlyingType) :
            _name(typeName),
            _id(dynamic_crc32(typeName)),
            _isPolymophic(isPolymophic),
            _size(byteSize),
            _ctor(ctor),
            _isSerializable(isSerializable),
            _isArray(isArray),
            _isEnum(isEnum),
            _underlyingType(&underlyingType) {
            auto name = _name;
            while(*(_name++) != ' ') { 
                if(*_name == '\0') { 
                    _name = name; break; 
                } 
            }
        }
        
        template <typename T>
        static const TypeInfo& get() {
            static TypeInfo typeInfo = 
                TypeInfo(typeid(T).name(), 
                sizeof(T), 
                TypeInfo::buildConstructor<T>(),
                std::is_convertible<T*, sly::ISerializable*>::value,
                std::is_polymorphic<T>::value,
                std::is_array<T>::value,
                std::is_enum<T>::value,
                TypeInfo::getUnderlyingType<T>()
                );

            return typeInfo;
        }

        template <typename T>
        static const TypeInfo create(vptr_t args = 0) { return reinterpret_cast<T*>(get<T>().create(args)); }
       
        inline const char* name() const { return _name; }
        inline size_t size() const { return _size; }
        inline type_id typeId() const { return _id; }
        inline bool_t isPolymophic() const { return _isPolymophic; }
        inline bool_t isSerializable() const { return _isSerializable; }
        inline const TypeInfo& underlyingType() const { return *_underlyingType; }
        inline bool_t isArray() const { return _isArray; }
        inline std::function<vptr_t(vptr_t)> const defaultConstructor() { return _ctor; }
        inline vptr_t const create(vptr_t args = 0) { return _ctor(args); }
        
        operator type_id() const { return this->_id; }
        operator const char*() const { return this->_name; }
    protected:
        type_id _id; 
        size_t _size;
        const char* _name;
        bool_t _isSerializable;
        bool_t _isPolymophic;
        bool_t _isArray;
        bool_t _isEnum;
        const TypeInfo* _underlyingType;

        std::function<vptr_t(vptr_t)> _ctor;

        template <typename T>
        static const std::function<vptr_t(vptr_t)> buildConstructor() {
            //static const std::function<vptr_t(vptr_t)> ctor = std::is_abstract<T>::value ? //nullptr : nullptr;
            //    (std::function<vptr_t(vptr_t)>)[](vptr_t buffer) { return (vptr_t)nullptr; } : 
            //    (std::function<vptr_t(vptr_t)>)[](vptr_t buffer) { return reinterpret_cast<vptr_t>(new (buffer) typename std::conditional<std::is_abstract<T>::value, u8, T>::type()); };
            //return ctor;

            return (std::function<vptr_t(vptr_t)>)[](vptr_t buffer) { return (vptr_t)nullptr; };            
        } 
        
        template <typename T>
        static const TypeInfo& getUnderlyingType() {

            static TypeInfo arrayInfo = 
                std::is_array<T>::value ? get<typename std::remove_extent<T>::type>() : TypeInfo();
                    (std::is_enum<T>::value ? get<typename safe_underlying_type<T>::type>() : TypeInfo());


            return arrayInfo;
        }

        TypeInfo() :
            _name("void"),
            _id(static_crc32("void")),
            _isPolymophic(false),
            _size(0),
            _ctor(nullptr),
            _isSerializable(false),
            _isArray(false),
            _isEnum(false),
            _underlyingType(nullptr) {
        }
    };

    class IHasTypeInfo {
    public:
        virtual ~IHasTypeInfo() {}

        virtual const sly::TypeInfo& getType() const = 0;

    protected:
        IHasTypeInfo() {}
    };

    #define SLY_TYPEINFO const sly::TypeInfo& getType() const { static const sly::TypeInfo instance = sly::TypeInfo::get<std::remove_reference<decltype(*this)>::type>(); return instance; }

}