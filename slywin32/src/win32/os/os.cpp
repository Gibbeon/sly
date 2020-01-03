#include "sly/win32/os/operatingsystem.h"

using namespace sly::os;


Win32OperatingSystem::Win32OperatingSystem() {

}

sly::retval<vptr_t> Win32OperatingSystem::loadLibrary(std::string moniker) {
    auto pf = LoadLibraryA(moniker.c_str());
    
    if(!pf) {
        return failed<vptr_t>(SLY_NOTFOUND, (ErrorMessage)"The LoadLibraryA function returned a null value for the requested file.");
    }
    
    return pf;
}

sly::retval<vptr_t> Win32OperatingSystem::getProcAddress(std::string moniker, vptr_t handle) {
    auto pf = GetProcAddress((HMODULE)handle, moniker.c_str());
    
    if(!pf) {
        return failed<vptr_t>(SLY_NOTFOUND, (ErrorMessage)"The GetProcAddress function returned a null value for the requested function.");
    }
    
    return pf;
}


/*size_t Win32OperatingSystem::getPluginRegistrationFunctions(sly::pfRegisterPlugins* ppfRegisterPlugins, size_t max) {
    HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    
    auto pf = GetProcAddress(h, "_RegisterPlugins");
    
    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)pf;
    count++;

    return count;
}*/