#include "sly/win32/os/systeminterface.h"

using namespace sly::os;

Win32SystemInterface::Win32SystemInterface(sly::Kernel& kernel) : 
    _kernel(kernel),
    _filesystem(nullptr),
    _windows(nullptr) {

}

Win32SystemInterface::~Win32SystemInterface() {

}

sly::retval<void> Win32SystemInterface::init() {
    static os::Win32FileSystem filesystem(_kernel);
    if(filesystem.init().failed()) {
        throw;
    } 
    
    _filesystem = &filesystem; 

    static os::Win32WindowSystem windows(_kernel);
    if(windows.init().failed()) {
        throw;
    } 
    
    _windows = &windows; 

    return success();
}

sly::retval<void> Win32SystemInterface::release() {
    return success();
}

sly::retval<vptr_t> Win32SystemInterface::loadLibrary(gsl::czstring_span<> moniker) {
    auto pf = LoadLibraryA(moniker.as_string_span().data());
    
    if(!pf) {
        return failed<vptr_t>(SLY_NOTFOUND, (ErrorMessage)"The LoadLibraryA function returned a null value for the requested file.");
    }
    
    return pf;
}

sly::retval<vptr_t> Win32SystemInterface::getProcAddress(gsl::czstring_span<> moniker, SystemHandle handle) {
    auto pf = GetProcAddress((HMODULE)handle, moniker.as_string_span().data());
    
    if(!pf) {
        return failed<vptr_t>(SLY_NOTFOUND, (ErrorMessage)"The GetProcAddress function returned a null value for the requested function.");
    }
    
    return pf;
}
            
IFileSystem& Win32SystemInterface::filesystem() const {
    Expects(_filesystem);
    return *_filesystem;
}

IWindowSystem& Win32SystemInterface::windows() const {
    Expects(_windows);
    return *_windows;
}


/*size_t Win32SystemInterface::getPluginRegistrationFunctions(sly::pfRegisterPlugins* ppfRegisterPlugins, size_t max) {
    HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    
    auto pf = GetProcAddress(h, "_RegisterPlugins");
    
    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)pf;
    count++;

    return count;
}*/