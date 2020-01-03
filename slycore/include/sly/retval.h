#pragma once

#include <type_traits>

#include "sly/macros.h"
#include "sly/types.h"

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
        retval(T value) : 
            _value(std::move(value)), 
            _statusCode(SUCCESS) {}
        
        retval(StatusCode code) : _statusCode(code) {}

        //retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;
        ~retval() = default;

        T& result() { return _value; }        
        operator T&() { return result(); }

        template <typename V>
        operator V() { return reinterpret_cast<V>(_value); }

        T& operator->() { return result(); }

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
        using TPointer = typename std::remove_reference<T>::type*;

        retval(T value) : 
            _value(std::addressof(value)), 
            _statusCode(SUCCESS) {}
        
        retval(StatusCode code) : _statusCode(code), _value(nullptr) {}

        retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;
        ~retval() = default;

        T result() { return *_value; }        
        operator T() { return result(); }
        TPointer operator->() { return _value; }

        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode() == SUCCESS; }
        bool_t failed() { return statusCode() != SUCCESS; }

    private:
        StatusCode _statusCode;
        TPointer _value;
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