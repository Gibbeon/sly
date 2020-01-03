#include "sly/macOS/os/os.h"
#include "sly/gfx/rendersystem.h"
#include "sly/metal/gfx/rendersystem.h"

using namespace sly::os;


MacOSOperatingSystem::MacOSOperatingSystem() {

}


void MacOSOperatingSystem::init() {

}   

void _RegisterMetalPlugin(sly::IPluginManager& manager) {
    static sly::gfx::METALRendererImpl instance;

    manager.set<sly::gfx::IRenderer>(instance);
}

size_t MacOSOperatingSystem::getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max) {
    /* HMODULE h = LoadLibraryA("c:/dev/sly/slyMETAL/bin/slyMETAL.dll");
    
    auto pf = GetProcAddress(h, "_RegisterPlugins");
    
    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)pf;
    count++; */

    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)_RegisterMetalPlugin;
    count++;

    return count;
}