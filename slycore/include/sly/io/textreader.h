#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/io/outputstream.h"

namespace sly { 
    template<size_t NBufferSize = 4096>
    class TextReader {
    public:
        TextReader(IInputStream& stream) : _stream(stream), _offset(0), _size(0), _position(0) { 
            //fill(); 
        }

        char_t* current()
        {
            return &_buffer[_offset];
        }

        bool_t eof() {
            return (_position + _offset) >= _stream.size();
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

        std::string read(std::function<bool_t(char_t)> until = [](char_t n) -> bool_t{ return std::isspace(n); } ) {            
            std::string sb;

            if(_position != _stream.position()) {
                fill();
            }

            size_t offset = _offset;

            while(!(until(*current())) && !eof()) {
                if(exhausted()) {
                     sb.append(&_buffer[offset], _size - offset);                     
                     _stream.seek(_size - offset); // on flush move the stream 
                     _size = offset = 0;
                }
                increment();
            }

            sb.append(&_buffer[offset], _size - offset); // on flush move the stream
            _stream.seek(_size - offset);

            _position = _stream.position();

            //_buffer[_offset] = '\0';
                        
            return sb;
        };

        std::string readLine() {
            return read([](char_t n) -> bool_t{ return n != '\n'; });
        };

        std::string readAll() {
            //return read([](char_t n) -> bool_t{ return false; });
            std::string result;
            result.reserve(_stream.size());
            result.resize(_stream.size());
            _stream.read(result.data(), _stream.size());
            return result;
        }; 

        bool_t fill() {
            if(! (_stream.position() >= _stream.size())) {
                _size = _stream.read(_buffer, MIN(NBufferSize,  _stream.size() - _stream.position()));     
                //_stream.seek(-((s32)_size)); // so we don't want to increment the stream until we actually read the data from the reader       
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