#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "sly/macOS/os/os.h"

#define BUF_SIZE 256

using namespace sly::os;

sly::retval<void> MacOSFileStream::open(const char_t* file) {
    int outError;
    struct stat statInfo;
 
    // Return safe values on error.
    outError = 0;
 
    // Open the file.
    _file = ::open( file, O_RDONLY, 0 );
    if( _file < 0 )
    {
       outError = errno;
        return failed<void>();
    }
    else
    {
        // We now know the file exists. Retrieve the file size.
        if( fstat( _file, &statInfo ) != 0 )
        {
            outError = errno;
            return failed<void>();
        }
        else
        {
            // Map the file into a read-only memory region.
            _data =         mmap(NULL,
                                statInfo.st_size,
                                PROT_READ,
                                MAP_PRIVATE,
                                _file,
                                0);
            if( _data == MAP_FAILED )
            {
                outError = errno;
                return failed<void>();
            }
            else
            {
                // On success, return the size of the mapped file.
                _size = statInfo.st_size;
            }
        }
 
        // Now close the file. The kernel doesn’t use our file descriptor.
        
    }
 
    return success();
}

size_t MacOSFileStream::read(vptr_t buffer, size_t size) {
    memcpy(buffer, _data, size);
    return size;
}

size_t MacOSFileStream::getSize() {
    return _size;
}

void MacOSFileStream::close() {
    munmap( _data, _size );
    ::close( _file );
}
