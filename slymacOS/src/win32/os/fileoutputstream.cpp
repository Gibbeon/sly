#include <windows.h>

#include "sly/win32/os/os.h"
#include "sly/gfx/rendersystem.h"

using namespace sly;

void Win32FileOutputStream::open(const char_t* file) {
    _file = std::fstream(file, std::ios::out | std::ios::binary);
}

void Win32FileOutputStream::write(vptr_t buffer, size_t size) {
    _file.write((char*)buffer, size);
}

void Win32FileOutputStream::close() {
    _file.close();
}

//    auto myfile = 
// 
// 
