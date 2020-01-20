#include "sly/win32/os/filesystem.h"
#include "sly/win32/os/filestream.h"

using namespace sly::os;

Win32FileSystem::Win32FileSystem(sly::Kernel& kernel) : _kernel(kernel) {

}

Win32FileSystem::~Win32FileSystem() {

}

sly::retval<void> Win32FileSystem::init(const FileSystemDesc& desc) {
    return success();
}

sly::retval<void> Win32FileSystem::release() {
    return success();
}

sly::retval<File> Win32FileSystem::open(gsl::czstring<> file) {
    auto stream = std::make_shared<Win32FileStream>();
    if(stream->open(file).failed()) {
        return failed<File>();
    }
    
    return File(stream);
}