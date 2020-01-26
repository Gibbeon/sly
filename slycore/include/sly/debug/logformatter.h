#pragma once

#include <vector>
#include <functional>
#include <sstream>

#include "sly/global.h"
#include "sly/debug/logmessage.h"
#include "sly/util/clock.h"

namespace sly {

    class LogFormatter {
    public:
        void init();

        static void writeTimestamp(LogMessage& msg, std::ostringstream& ostream);
        static void writeThreadId(LogMessage& msg, std::ostringstream& ostream);
        static void writeLevel(LogMessage& msg, std::ostringstream& ostream);
        static void writeMessage(LogMessage& msg, std::ostringstream& ostream);
        static void writeLineClass(LogMessage& msg, std::ostringstream& ostream);

        std::string format(eLogType type, eLogLevel level, gsl::czstring<> cls, gsl::czstring<> line, gsl::czstring<> fmt, va_list args);
        
    protected:
        std::vector<std::function<void(LogMessage&, std::ostringstream&)>>   _prepend;
        std::vector<std::function<void(LogMessage&, std::ostringstream&)>>   _append;
        std::function<void(LogMessage&, std::ostringstream&)>                _formatter;
    };
}