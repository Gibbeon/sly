#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/io/outputstream.h"

namespace sly {
   
    class BinaryWriter {
    public:
        BinaryWriter(IOutputStream& stream) : _stream(stream) {}
        
        template<typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        void write(T data, size_t size) {
            _stream.write((vptr_t)data, size);
        }

        template<typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        auto write(T& data, size_t size = sizeof(T)) {
            write(&data, size);
        }

        template<typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        auto write(T data, size_t size = sizeof(T)) {
            write(&data, size);
        }

    protected:
        IOutputStream& _stream;
    };    

      
}