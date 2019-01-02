#include "sly/global.h"
#include "sly/win32/sys/os.h"

void _CreateOperatingSystemImpl(sly::sys::IOperatingSystem** os) {
    (*os) = new sly::sys::Win32OperatingSystem();
}