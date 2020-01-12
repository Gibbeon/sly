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

    template<typename T, bool_t>
    struct Convert;

    template<typename T, bool_t = true>
    struct Convert {
    public:
        using type = T;

        /*template<typename U, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
        static U parse(String str) {
            char_t* end;
            return (T)std::strtoull(str.c_str(), &end, 10);
        }

        template<typename U, typename std::enable_if<std::is_floating_point<U>::value, float>::type = 0>
        static U parse(String str) {
            char_t* end;
             return (U)std::strtold(str.c_str(), &end);
        }

        template<typename U, typename std::enable_if<std::is_enum<U>::value, int>::type = 0>
        static U parse(String str) {
            return Enum<U>::parse(str);
        }

        //template<typename T, typename std::enable_if<std::is_enum<T>::value, int>::type = 0>
        static String parse(String str) {
            return str;
        }*/
    };  

    //template <typename U, bool_t> Convert(String) -> Convert<String, true>;

    
    template<size_t NBufferSize = 4096>
    class TextReader {
    public:
        TextReader(IInputStream& stream) : _stream(stream), _offset(0), _size(0), _position(0) { 
            fill(); 
        }

        char_t* current()
        {
            return &_buffer[_offset];
        }

        bool_t eof() {
            return _stream.getPosition() >= _stream.getSize();
        }

        bool_t increment()
        {
            if(exhausted() && !eof())
            {
                return fill();
            } else {
                _offset++;
            }

            return _offset < _size;
        }

        bool_t exhausted()
        {
            return _offset == _size;
        }

        template<typename T> 
        std::string read(std::function<bool_t(char_t)> until = [](char_t n) -> bool_t{ return std::isspace(n); } ) {            
            std::string sb;

            if(_position != _stream.getPosition()) {
                fill();
            }

            size_t offset = _offset;

            while(!(until(*current()))&& !eof()) {
                if(exhausted()) {
                     sb.append(&_buffer[offset], _size - offset);                     
                     _stream.seek(_size - offset); // on flush move the stream 
                     _size = offset = 0;
                }
                increment();
            }

            sb.append(&_buffer[offset], _size - offset); // on flush move the stream
            _stream.seek(_size - offset);

            _position = _stream.getPosition();

            _buffer[_offset] = '\0';
                        
            return sb;
        };

        std::string readLine() {
            return read([](char_t n) -> bool_t{ return n != '\n'; });
        };

        std::string readAll() {
            return read<gsl::czstring<>>([](char_t n) -> bool_t{ return false; });
        }; 

        bool_t fill() {
            if(! (_stream.getPosition() >= _stream.getSize())) {
                _size = _stream.read(_buffer, MIN(NBufferSize,  _stream.getSize() - _stream.getPosition()));     
                _stream.seek(-((s32)_size)); // so we don't want to increment the stream until we actually read the data from the reader       
                _offset = 0;
                return true;
            }
            return false;
        }

    protected:
        IInputStream& _stream;
        char _buffer[NBufferSize];
        size_t _offset;
        size_t _size;
        size_t _position;
    };    
}