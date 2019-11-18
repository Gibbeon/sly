#include "sly/global.h"
#include "sly/macOS/os/os.h"
#include "sly/metal/gfx/rendersystem.h"

using namespace sly;

os::IOperatingSystem* _GetOperatingSystem() {
    static sly::os::MacOSOperatingSystem instance;
    return &instance;
}

extern "C" void _RegisterPlugins(sly::IPluginManager& manager) {
    static sly::gfx::METALRenderSystemImpl instance;

    manager.set<sly::gfx::IRenderSystem>(instance);
};
