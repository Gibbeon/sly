#include "sly/macOS/os/os.h"
#include "sly/gfx/rendersystem.h"

using namespace sly;

void MacOSFileOutputStream::open(const char_t* file) {
    _file = std::fstream(file, std::ios::out | std::ios::binary);
}

void MacOSFileOutputStream::write(vptr_t buffer, size_t size) {
    _file.write((char*)buffer, size);
}

void MacOSFileOutputStream::close() {
    _file.close();
}