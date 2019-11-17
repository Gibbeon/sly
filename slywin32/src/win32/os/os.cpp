#include "sly/win32/os/os.h"
#include "sly/gfx/rendersystem.h"

using namespace sly::os;


Win32OperatingSystem::Win32OperatingSystem() {

}


void Win32OperatingSystem::init() {

}   

size_t Win32OperatingSystem::getPluginRegistrationFunctions(sly::pfRegisterPlugins* ppfRegisterPlugins, size_t max) {
    HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    
    auto pf = GetProcAddress(h, "_RegisterPlugins");
    
    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)pf;
    count++;

    return count;
}