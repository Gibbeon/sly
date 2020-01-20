#include "sly/global.h"
#include "sly/kernel.h"
#include "sly/win32/os/systeminterface.h"

//using namespace sly;

sly::os::ISystemInterface*  sly::os::GetSystemInterface(sly::Kernel& kernel) {
    static sly::os::Win32SystemInterface instance(kernel);
    static bool_t initialized = false;
    
    if(!initialized) {
        instance.init();
        initialized = true;
    }

    return &instance;
}