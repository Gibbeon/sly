#include "sly/global.h"
#include "sly/win32/os/operatingsystem.h"

//using namespace sly;

sly::os::IOperatingSystem*  sly::os::_GetOperatingSystem() {
    static sly::os::Win32OperatingSystem instance;
    return &instance;
}