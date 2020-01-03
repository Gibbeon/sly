#include "sly/os/operatingsystem.h"

sly::retval<void> sly::os::OperatingSystem::init(sly::os::OperatingSystemDesc&) { 
    _impl = _GetOperatingSystem(); return success(); 
}