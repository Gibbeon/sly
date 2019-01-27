#include <windows.h>

#include "sly/win32/os/os.h"
#include "sly/gfx/rendersystem.h"

using namespace sly;

void Win32FileOutputStream::open(const char_t* file) {
    _file = std::fstream(file, std::ios::out | std::ios::binary);
}

void Win32FileOutputStream::write(vptr_t buffer, size_t size) {
    _file.write((char *)buffer, size);
}

void Win32FileOutputStream::close() {
    _file.close();
}

void Win32FileOutputStream::seek(size_t offset) {
    _file.seekp(offset, std::ios_base::cur);
}

size_t Win32FileOutputStream::getPosition() {
    return _file.tellp();
}
void Win32FileOutputStream::setPosition(size_t position) {
    _file.seekp(position);
}

size_t Win32FileOutputStream::getSize() {
    return _file.tellg();
}


//    auto myfile = 
// 
// 
