#include "sly/global.h"
#include "sly/macOS/os/os.h"

using namespace sly;

os::IOperatingSystem* _GetOperatingSystem() {
    static sly::os::MacOSOperatingSystem instance;
    return &instance;
}