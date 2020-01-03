#include "sly/global.h"
#include "sly/macOS/os/os.h"
#include "sly/metal/gfx/renderer.h"

using namespace sly;

os::IOperatingSystem* sly::os::_GetOperatingSystem() {
    static sly::os::MacOSOperatingSystem instance;
    return &instance;
}