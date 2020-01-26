#pragma once

#include "sly/global.h"

namespace sly {
    class LogFormatter;
    class LogWriter;
    class LogConfig {
    public:
        retval<void> configureWriter(LogWriter& writer);
        retval<void> configureFormatter(LogFormatter& formatter);
    };
}