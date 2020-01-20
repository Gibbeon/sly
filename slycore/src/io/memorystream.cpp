#include "sly/io/memorystream.h"

using namespace sly;

MemoryStream::MemoryStream() {

}


MemoryStream::MemoryStream(size_t length) {
    _buffer.reserve(length);
}

MemoryStream::~MemoryStream() {}

retval<size_t>  MemoryStream::read(vptr_t buffer, size_t size) {
    if((_position + size) > _buffer.size()) {
        size = _buffer.size() - _position;
    }

    if(size > 0) {
        auto span = gsl::span((byte_t*)buffer, size);

        std::copy(_buffer.begin() + _position, _buffer.begin() + _position + size, span.begin());

        _position += size;
    }

    return _position;
}

retval<void>    MemoryStream::write(vptr_t data, size_t size) {
    if((_position + size) > _buffer.size()) {
        _buffer.resize(_position + size);
    }

    auto span = gsl::span((byte_t*)data, size);

    std::copy(span.begin(), span.end(), _buffer.begin() + _position);

    _position += size;

    return success();
}

size_t MemoryStream::size() const {
    return _buffer.size();
}

size_t MemoryStream::position() const {
    return _position;
}

retval<void> MemoryStream::seek(s64 offset) {
    if((_position + offset) < 0 || (_position + offset) >= _buffer.size()) {
        return failed();
    }

    _position += offset;
    return success();
}

retval<void> MemoryStream::setPosition(size_t position) {
    _position = position;
    return success();
}

retval<void> MemoryStream::flush() {
    return success();

}

retval<void> MemoryStream::close() {
    return success();

}