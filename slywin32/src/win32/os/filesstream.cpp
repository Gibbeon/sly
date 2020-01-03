#undef UNICODE 
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "sly/win32/os/operatingsystem.h"

#define BUF_SIZE 256

using namespace sly::os;

sly::retval<void> Win32FileStream::open(const char_t* file) {

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
        return failed<void>((sly::StatusCode)value, (sly::ErrorMessage)GetLastErrorMessage().c_str());
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
        
        return failed<void>((sly::StatusCode)value, (sly::ErrorMessage)GetLastErrorMessage().c_str());
    }

    return success();
}

size_t Win32FileStream::read(vptr_t buffer, size_t size) {
    CopyMemory(buffer, (vptr_t)((size_t)_file + _offset), size);
    _offset += size;
    return size;
}

size_t Win32FileStream::getSize() {
    return _size;
}

void Win32FileStream::close() {
    UnmapViewOfFile(_file);

    CloseHandle(_handle);
}

//    auto myfile = std::fstream("file.binary", std::ios::out | std::ios::binary);
// myfile.write((char*)&data[0], bytes);
// myfile.close();
