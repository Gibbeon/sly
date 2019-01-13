#include "sly/win32/os/os.h"
#include "sly/gfx/rendersystem.h"
#include "sly/engine.h"

using namespace sly;

typedef void (APIENTRY * pfRegisterPlugins) (sly::IPluginManager& );

Win32OperatingSystem::Win32OperatingSystem() {

}


void Win32OperatingSystem::init() {
    loadModules();
}   

void Win32OperatingSystem::loadModules() {
    HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    
    auto pf = (pfRegisterPlugins)GetProcAddress(h, "_RegisterPlugins");

    pf(Engine::Plugins());
}