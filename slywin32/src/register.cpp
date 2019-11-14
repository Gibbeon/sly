#include "sly/global.h"
#include "sly/win32/os/os.h"

//using namespace sly;

sly::os::IOperatingSystem* _GetOperatingSystem() {
    static sly::os::Win32OperatingSystem instance;
    return &instance;
}