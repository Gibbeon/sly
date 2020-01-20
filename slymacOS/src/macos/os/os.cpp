#include "sly/macOS/os/os.h"
#include "sly/gfx/graphicsystem.h"
#include "sly/gfx/renderer.h"
#include "sly/metal/gfx/renderer.h"

using namespace sly::os;


MacOSSystemInterface::MacOSSystemInterface() {

}


sly::retval<void> MacOSSystemInterface::init(SystemInterfaceDesc&) {
    static sly::gfx::METALRenderInterface instance;
    sly::gfx::RenderSystem::addRenderer(&instance);

    return success();
}   

/*
void _RegisterMetalPlugin(sly::IPluginManager& manager) {
    static sly::gfx::METALRenderInterface instance;

    manager.set<sly::gfx::IRenderInterface>(instance);
}

size_t MacOSSystemInterface::getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max) {
    /* HMODULE h = LoadLibraryA("c:/dev/sly/slyMETAL/bin/slyMETAL.dll");
    
    auto pf = GetProcAddress(h, "_RegisterPlugins");
    
    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)pf;
    count++; */
    /*

    size_t count = 0;
    ppfRegisterPlugins[count] = (pfRegisterPlugins)_RegisterMetalPlugin;
    count++;

    return count;
}*/