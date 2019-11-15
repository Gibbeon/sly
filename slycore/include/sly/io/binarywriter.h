#pragma once

#include "sly/global.h"
#include "sly/io/istream.h"
#include "sly/io/ostream.h"

namespace sly {
    class TextWriter {
    public:
        TextWriter(IOutputStream& stream) : _stream(stream) {}

        void write(const char* data) {
            _stream.write((vptr_t)data, strlen(data));
        }

        void writeline(const char* data) {
            write(data);
            write("\n");
        }

        template<typename T> 
        void write(T object) {
            //write(reinterpret_cast<vptr_t>(&object), sizeof(T));
        };

        template<> 
        void write<u32>(u32 value) {
            _itoa_s(value, buffer, 10);
            write(buffer);
        };
        template<> 
        void write<size_t>(size_t value) {
            _i64toa_s(value, buffer, sizeof(buffer), 10);
            write(buffer);
        };
    protected:
        IOutputStream& _stream;
        char buffer[128];
    };    

    class TextReader {
    public:
        TextReader(IInputStream& stream) : _stream(stream), _offset(0) {}

        std::string readAll() {
            std::string result(_stream.getSize(), ' ');
            _stream.read(const_cast<char*>(result.c_str()), _stream.getSize());
            return result;
        }

        /*template<typename T> 
        T read() {
            //write(reinterpret_cast<vptr_t>(&object), sizeof(T));
        };

        template<> 
        u32 read<u32>() {
            u32 data;

            if(_offset > 4064) {
                memcpy(_buffer, &_buffer[_offset], sizeof(_buffer) - _offset); // copy tail data
                _stream.read(&_buffer[_offset], sizeof(_buffer) - _offset); // read in new data
                _offset = 0; // reset offset
            }

            char* ptr = &_buffer[_offset];
            data = atoi(ptr);
            return data;
        };*/
    protected:
        IInputStream& _stream;
        char _buffer[4096];
        size_t _offset;
    };    

    class BinaryWriter {
    public:
        BinaryWriter(IOutputStream& stream) : _stream(stream) {}

        void write(vptr_t data, size_t size) {
            _stream.write(data, size);
        }

        template<typename T> 
        void write(T object) {
            write(reinterpret_cast<vptr_t>(&object), sizeof(T));
        };
    protected:
        IOutputStream& _stream;
    };    

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