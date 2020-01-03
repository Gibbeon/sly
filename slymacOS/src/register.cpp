#include "sly/global.h"
#include "sly/macOS/os/os.h"
#include "sly/metal/gfx/renderer.h"

using namespace sly;

os::IOperatingSystem* sly::os::_GetOperatingSystem() {
    static sly::os::MacOSOperatingSystem instance;
    static bool_t initialized = false;
    if(!initialized) {
        instance.init(sly::os::OperatingSystemBuilder().build());
        initialized = true;
    }

    return &instance;
}