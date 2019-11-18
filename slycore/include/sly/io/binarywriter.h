#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/io/outputstream.h"

namespace sly {
   
    template<typename T = const std::string>
    class StringType
    {   
    public:
        StringType(size_t size, char_t defaultValue = '\0') :
            string(size, defaultValue) 
        {
        }

        StringType(std::string& init_value) :
            string(init_value) 
        {
        }

        const char_t* c_str() {
            return string.c_str();
        }

        size_t length() {
            return string.length();
        }

        operator const char_t*() { return c_str(); }        
        operator std::string() { return string; }

    private:
        std::string string;
    };

    using String = StringType<>;

    template<>
    class StringType<const char_t*>
    {
    public:
        StringType() :
            string(NULL) 
        {
        }

        StringType(const char_t* init_value) :
            string(init_value) 
        {
        }

        const char_t* c_str() const {
            return string;
        }

        size_t length() const {
            return strlen(string);
        }

        operator const char_t*() { return c_str(); }        
        operator std::string() { return string; }

    private:
        const char_t* string;
    };

    template<>
    class StringType<std::string&>
    {
        StringType(std::string& init_value) :
            string(init_value) 
        {
        }

        const char_t* c_str() {
            return string.c_str();
        }

        size_t length() {
            return string.length();
        }

        operator const char_t*() { return c_str(); }        
        operator std::string() { return string; }

    private:
        std::string& string;
    };

    template<>
    class StringType<std::string>
    {
    public:

    };


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

        void write(String string) {
            write(string.length());
            write(string.c_str(), string.length());
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

        void write(String data) {
            _stream.write((vptr_t)data.c_str(), data.length());
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

        template<> 
        String read<String>() {
            size_t size = read<size_t>();

            String str(size);
            read((vptr_t)str.c_str(), size);
            return str;
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

        template<typename U, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
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
        }
    };  

    //template <typename U, bool_t> Convert(String) -> Convert<String, true>;

    
    template<size_t NBufferSize = 4096>
    class TextReader {
    public:
        TextReader(IInputStream& stream) : _stream(stream), _offset(0), _size(0), _position(-1) { 
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
        String read(std::function<bool_t(char_t)> until = [](char_t n) -> bool_t{ return std::isspace(n); } ) {            
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
                        
            return Convert<T>::parse(sb);
        };

        String readLine() {
            return read([](char_t n) -> bool_t{ return n != '\n'; });
        };

        String readAll() {
            return read<String>([](char_t n) -> bool_t{ return false; });
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