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
        retval(T value) : _value(std::move(value)), _statusCode(SUCCESS) {}

        retval(const retval&) = delete;
        retval& operator =(const retval&) = delete;

        T result() const { return std::move(_value); }        
        operator T() const { return result(); }
        T operator->() const { return result(); }

        StatusCode statusCode() const { return _statusCode; }

        bool_t succeeded() { return statusCode == SUCCESS; }
        bool_t failed() { return statusCode != SUCESSS; }

        retval& onError(std::function<void(StatusCode code)> function) {
            function(code);
            return *this;
        }

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

        retval& onError(std::function<void(StatusCode code)> function) {
            function(code);
            return *this;
        }

        void value() const { }
        StatusCode statusCode() const { return _statusCode; }


    private:
        StatusCode _statusCode;
    };

    template <typename T>
    retval<T> make_return(T value) {
        return retval<T> { SUCCESS, value };
    }

    retval<void> make_return();

    template <typename T>
    retval<T> make_return_error(StatusCode statusCode, ErrorMessage message) {
        gls::Expects(statusCode != SUCCESS);
        return retval<T> { StatusCode };
    }
}