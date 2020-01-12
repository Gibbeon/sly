#pragma once

#include "sly/global.h"

namespace sly {
    class TextWriter {
    public:
        TextWriter(IOutputStream& stream) : _stream(stream) {}

        template<typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        auto write(T& data, size_t size = sizeof(T)) {
            write(std::to_string(data));
        }

        template<typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        auto write(T data, size_t size = sizeof(T)) {
            write(std::to_string(data));
        }
       

    protected:
        IOutputStream& _stream;
    };  
}