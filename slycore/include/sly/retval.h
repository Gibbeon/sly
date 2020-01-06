#pragma once

#include <type_traits>
#include <gsl/gsl>

#include "sly/macros.h"
#include "sly/types.h"

template <class T>
struct is_unique_ptr : std::false_type
{};

template <class T, class D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
{};

template <class T>
struct unique_ptr_type
{};

template <class T, class D>
struct unique_ptr_type<std::unique_ptr<T, D>>
{    
    using type = std::unique_ptr<T, D>;
    using underlying_type = T;
    using delete_type = D;
};

template <class T>
struct is_shared_ptr : std::false_type
{};

template <class T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type
{};

namespace sly {
    typedef s32 StatusCode;
    typedef const char* ErrorMessage;


    static const StatusCode SUCCESS = (StatusCode)0;
    static const StatusCode UNKNOWN = (StatusCode)-1;

    template <typename T, typename = typename std::is_reference<T>::type>
    struct retval { };

    template <typename T>
    struct retval<T, std::false_type> { 
    public:
    
        using type = T;
        using type_pointer = typename std::remove_reference<T>::type*;
        using type_reference = typename std::remove_reference<T>::type&;
    
        //using unique_ptr = typename is_unique_ptr<T>::value;

        retval(T value) : 
            _value(std::move(value)), 
            _statusCode(SUCCESS) {}
        
        retval(StatusCode code) : _statusCode(code) {}

        //retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;
        ~retval() = default;

        template <class V, typename Y = T, typename std::enable_if_t<is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>
        V to() const {
            return reinterpret_cast<V>(_value.get());
        }

        template <class V, typename Y = T, typename std::enable_if_t<!is_unique_ptr<Y>::value && !is_shared_ptr<Y>::value>* = nullptr>
        V to() const {            
            return reinterpret_cast<V>(_value);
        }

        template<typename V>
        operator V() const {
            return to<V>();
        }

        type_reference result() { return _value; }  
        
        template <typename Y = T, typename std::enable_if_t<is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>  
        operator type_reference() const { 
            return *_value.get(); 
        }  

        template <typename Y = T, typename std::enable_if_t<is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>  
        operator typename unique_ptr_type<Y>::underlying_type&() { 
            return *_value.get(); 
        }  

        template <typename Y = T, typename std::enable_if_t<!is_unique_ptr<Y>::value && !is_shared_ptr<Y>::value>* = nullptr>      
        operator type_reference() { return result(); }   

        template <typename Y = T, typename std::enable_if_t<std::is_pointer<Y>::value || is_unique_ptr<Y>::value || is_shared_ptr<Y>::value>* = nullptr>
        type_reference operator->() { return _value; }

        template <typename Y = T, typename std::enable_if_t<!std::is_pointer<Y>::value && !is_unique_ptr<Y>::value && !is_shared_ptr<Y>::value>* = nullptr>
        type_pointer operator->() { return &_value; }

        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode() == SUCCESS; }
        bool_t failed() { return statusCode() != SUCCESS; }

    private:
        StatusCode _statusCode;
        T _value;
    };

    template <typename T>
    struct retval<T, std::true_type> { 
    public:
        
        using type = T;
        using type_pointer = typename std::remove_reference<T>::type*;

        retval(T value) : 
            _value(std::addressof(value)), 
            _statusCode(SUCCESS) {}
        
        retval(StatusCode code) : _statusCode(code), _value(nullptr) {}

        retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;
        ~retval() = default;

        T result() { return *_value; }        
        operator T() { return result(); }
        type_pointer operator->() { return _value; }
           
        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode() == SUCCESS; }
        bool_t failed() { return statusCode() != SUCCESS; }

    private:
        StatusCode _statusCode;
        type_pointer _value;
    };


    template <>
    struct retval<void, std::false_type> {
    public:   
        retval() : _statusCode(SUCCESS) {}
        retval(StatusCode code) : _statusCode(code) {}

        retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;
        ~retval() = default;

        void value() const { }        
        
        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode() == SUCCESS; }
        bool_t failed() { return statusCode() != SUCCESS; }


    private:
        StatusCode _statusCode;
    };

    template <typename T>
    retval<T> value(const T& value) {
        auto result = retval<T> ( std::move(value) ) ;
        return result;
    }

    template <typename T>
    retval<T&> reference(T& value) {
        return retval<T&> ( value );
    }

    retval<void> success();

    template <typename T>
    retval<T> failed(StatusCode statusCode, ErrorMessage message) {
        
        Expects(statusCode != SUCCESS);
        return retval<T> { statusCode };
    }

    template <typename T>
    retval<T> failed() {        
        return retval<T> { UNKNOWN };
    }
}