#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "sly/macOS/os/os.h"

#define BUF_SIZE 256

using namespace sly::os;

void MacOSFileInputStream::open(const char_t* file) {
    int outError;
    int fileDescriptor;
    struct stat statInfo;
 
    // Return safe values on error.
    outError = 0;
 
    // Open the file.
    fileDescriptor = ::open( file, O_RDONLY, 0 );
    if( fileDescriptor < 0 )
    {
       outError = errno;
    }
    else
    {
        // We now know the file exists. Retrieve the file size.
        if( fstat( fileDescriptor, &statInfo ) != 0 )
        {
            outError = errno;
        }
        else
        {
            // Map the file into a read-only memory region.
            _file = mmap(NULL,
                                statInfo.st_size,
                                PROT_READ,
                                0,
                                fileDescriptor,
                                0);
            if( _file == MAP_FAILED )
            {
                outError = errno;
            }
            else
            {
                // On success, return the size of the mapped file.
                _size = statInfo.st_size;
            }
        }
 
        // Now close the file. The kernel doesn’t use our file descriptor.
        ::close( fileDescriptor );
    }
 
    //return outError;
}

size_t MacOSFileInputStream::read(vptr_t buffer, size_t size) {

}

size_t MacOSFileInputStream::getSize() {
    return _size;
}

void MacOSFileInputStream::close() {
    munmap( _file, _size );
}
