#include "sly/global.h"
#include "sly/macOS/os/os.h"

using namespace sly;

IOperatingSystem* _GetOperatingSystem() {
    static sly::MacOSOperatingSystem instance;
    return &instance;
}