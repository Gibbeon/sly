#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/io/outputstream.h"

namespace sly {
    class BinaryReader {
    public:
        BinaryReader(IInputStream& stream) : _stream(stream) {}

        void read(vptr_t data, size_t size) {
            _stream.read(data, size);
        }

        template<typename T> 
        T read() {
            T data;
            read(&data, sizeof(T));
            return data;
        };

    protected:
        IInputStream& _stream;
    };      
}