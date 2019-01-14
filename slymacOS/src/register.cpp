#include "sly/global.h"
#include "sly/win32/os/os.h"

using namespace sly;

IOperatingSystem* _GetOperatingSystem() {
    static sly::Win32OperatingSystem instance;
    return &instance;
}