#include "sly/global.h"
#include "sly/macOS/os/os.h"

using namespace sly;

os::ISystemInterface* sly::os::GetSystemInterface() {
    static sly::os::MacOSSystemInterface instance;
    static bool_t initialized = false;
    
    if(!initialized) {
        instance.init(sly::os::SystemInterfaceBuilder().build());
        initialized = true;
    }

    return &instance;
}