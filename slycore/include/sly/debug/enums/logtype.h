#pragma once

#include "sly/global.h"

namespace sly {

    ENUM_DECL(eLogType,
        eLogType_Logger,
        eLogType_Debugger,
        eLogType_Profiler,
        eLogType_Count
    );
}