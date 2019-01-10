#include "sly/global.h"
#include "sly/win32/os/os.h"

void _CreateOperatingSystemImpl(sly::os::IOperatingSystem** os) {
    (*os) = new sly::os::Win32OperatingSystem();
}