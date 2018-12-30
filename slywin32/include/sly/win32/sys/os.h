#pragma once

#include "sly/win32.h"
#include "sly/sys/os.h"

namespace sly {
    namespace sys {
        class Win32OperatingSystem : public IOperatingSystem {
        public:
            Win32OperatingSystem();

        };
    }
}