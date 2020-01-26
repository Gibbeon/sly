#pragma once

#include <varargs.h>

#include "sly/global.h"
#include "sly/debug/enums/loglevel.h"
#include "sly/debug/enums/logtype.h"

namespace sly {
    struct LogMessage {
    public:
        eLogType type;
        eLogLevel level;
        gsl::czstring<> cls;     
        gsl::czstring<> line;
        gsl::czstring<> fmt;
        va_list args;
    };  
}