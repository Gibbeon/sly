#pragma once

#include "sly/global.h"
#include "sly/io/outputstream.h"

namespace sly {
    class TextWriter {
    public:
        TextWriter(IOutputStream& stream) : _stream(stream) {}

        template<typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        auto write(const T& data, size_t size = sizeof(T)) {
            write(std::to_string(data));
        }

        template<typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        auto write(T data, size_t size = sizeof(T)) {
            write(std::to_string(data));
        }

        auto write(std::string data) {
            _stream.write(data.data(), data.size());
        }      

    protected:
        IOutputStream& _stream;
    };  
}