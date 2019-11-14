#include "sly/macOS/os/os.h"
#include "sly/gfx/rendersystem.h"

using namespace sly::os;


MacOSOperatingSystem::MacOSOperatingSystem() {

}


void MacOSOperatingSystem::init() {

}   

size_t MacOSOperatingSystem::getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max) {
    /* HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    
    auto pf = GetProcAddress(h, "_RegisterPlugins");
    
    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)pf;
    count++; */

    return 0;
}