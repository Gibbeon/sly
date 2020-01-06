#include "sly/os/operatingsystem.h"

using namespace sly::os;

OperatingSystem::OperatingSystem(sly::Kernel& kernel) : 
    _kernel(kernel), 
    _system(nullptr) {

}        

OperatingSystem::~OperatingSystem() {

} 

sly::retval<void> OperatingSystem::init() {
    _system = GetSystemInterface(_kernel);

    return success();
}

sly::retval<void> OperatingSystem::release() {
    return success();
}

sly::retval<IOperatingSystem::SystemHandle> OperatingSystem::loadLibrary(gsl::czstring_span<> moniker) {
    return (IOperatingSystem::SystemHandle)nullptr;
}

sly::retval<IOperatingSystem::SystemHandle> OperatingSystem::getProcAddress(gsl::czstring_span<> moniker, IOperatingSystem::SystemHandle handle) {
    return (IOperatingSystem::SystemHandle)nullptr;
}

IFileSystem& OperatingSystem::filesystem() const {
    return _system->filesystem();

}

IWindowSystem&  OperatingSystem::windows() const {
    return _system->windows();
}
