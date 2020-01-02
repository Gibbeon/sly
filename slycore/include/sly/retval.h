#pragma once

#include "sly/macros.h"
#include "sly/types.h"

namespace sly {
    typedef s32 StatusCode;
    typedef const char* ErrorMessage;

    static const StatusCode SUCCESS = (StatusCode)0;
    static const StatusCode UNKNOWN = (StatusCode)-1;

    template <typename T>
    struct retval {
    public:
        retval(T value) : 
            _value(std::move(value)), 
            _statusCode(SUCCESS) {}

        retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;

        T result() { return std::move(_value); }        
        operator T() { return result(); }
        T operator->() { return result(); }

        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode() == SUCCESS; }
        bool_t failed() { return statusCode() != SUCCESS; }

    private:
        StatusCode _statusCode;
        T _value;
    };

    template <>
    struct retval<void> {
    public:   
        retval() : _statusCode(SUCCESS) {}

        retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;

        void value() const { }        
        
        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode() == SUCCESS; }
        bool_t failed() { return statusCode() != SUCCESS; }


    private:
        StatusCode _statusCode;
    };

    template <typename T>
    retval<T> return_value(const T& value) {
        return retval<T> ( value );
    }

    template <typename T>
    retval<T&> return_reference(T& value) {
        return retval<T&> ( value );
    }

    retval<void> return_void();

    template <typename T>
    retval<T> return_error(StatusCode statusCode, ErrorMessage message) {
        gls::Expects(statusCode != SUCCESS);
        return retval<T> { StatusCode };
    }
}