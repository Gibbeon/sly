#undef UNICODE 
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "sly/win32/os/os.h"
#include "sly/gfx/rendersystem.h"
#include "sly/platform.h"

#define BUF_SIZE 256

using namespace sly::os;

void Win32FileInputStream::open(const char_t* file) {

    HANDLE hFile = CreateFile(file, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0);

    LARGE_INTEGER lpFileSize;
    GetFileSizeEx(hFile, &lpFileSize);

    _size = lpFileSize.QuadPart;

    _handle = CreateFileMapping(
                    hFile,                  // use paging file
                    NULL,                    // default security
                    PAGE_READONLY,          // read/write access
                    0,                       // maximum object size (high-order DWORD)
                    _size,                // maximum object size (low-order DWORD)
                    NULL);                 // name of mapping object

    if (_handle == NULL)
    {
        auto value = GetLastError();
        return;
    } 
    
    _file = MapViewOfFile(  _handle,   // handle to map object
                            FILE_MAP_READ, // read/write permission
                            0,
                            0,
                            _size);

    if (_file == NULL)
    {
        auto value = GetLastError();
        CloseHandle(_handle);

        /* return 1; */
    }
}

void Win32FileInputStream::read(vptr_t buffer, size_t size) {
    CopyMemory(buffer, _file, size);
}

size_t Win32FileInputStream::getSize() {
    return _size;
}

void Win32FileInputStream::close() {
    UnmapViewOfFile(_file);

    CloseHandle(_handle);
}

//    auto myfile = std::fstream("file.binary", std::ios::out | std::ios::binary);
// myfile.write((char*)&data[0], bytes);
// myfile.close();
