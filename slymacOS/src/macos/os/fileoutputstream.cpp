/*#include "sly/macOS/os/os.h"

using namespace sly::os;

void MacOSFileOutputStream::open(const char_t* file) {
    _file = std::fstream(file, std::ios::out | std::ios::binary);
}

void MacOSFileOutputStream::write(vptr_t buffer, size_t size) {
    _file.write((char*)buffer, size);
}

void MacOSFileOutputStream::close() {
    _file.close();
}

void MacOSFileOutputStream::seek(s32 offset) {
    _file.seekp(offset, std::ios_base::cur);
}

size_t MacOSFileOutputStream::getPosition() {
    return _file.tellp();
}
void MacOSFileOutputStream::setPosition(size_t position) {
    _file.seekp(position);
}

size_t MacOSFileOutputStream::getSize() {
    return _file.tellg();
}
*/
