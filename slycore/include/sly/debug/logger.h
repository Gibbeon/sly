#pragma once

#include "sly/global.h"
#include "sly/debug/logmessage.h"
#include "sly/debug/logformatter.h"
#include "sly/debug/logconfig.h"
#include "sly/debug/logwriter.h"

namespace sly { 
 
    class ILogger {
    public:
        virtual void log(eLogType, eLogLevel, gsl::czstring<>, gsl::czstring<>, gsl::czstring<>, ...) = 0;

    };

    template<typename T = void>
    class Logger : public ILogger {
    public:
        Logger() {
            if(!_initialized) {
                static std::mutex mutex;
                std::scoped_lock lock(mutex);
                if(!_initialized) {
                    LogConfig config;
                    for(auto i = 0; i < eLogType_Count; i++) {
                        config.configureFormatter(_formatter[i]);
                        config.configureWriter(_writer[i]);
                    }
                    _initialized = true;
                }
            }
        }

        virtual void log(eLogType type, eLogLevel level, gsl::czstring<> cls,gsl::czstring<> line,gsl::czstring<> fmt, ...) {
            static std::mutex mutex;
            std::scoped_lock lock(mutex);
            va_list args;
            va_start(args, fmt);
            _writer[type].write(_formatter[type].format(type, level, cls, line, fmt, args));
            va_end(args);
        }    

    protected:
        static LogWriter        _writer     [eLogType_Count];
        static LogFormatter     _formatter  [eLogType_Count];
        static bool_t           _initialized;
    };  

    template<typename T>
    LogWriter       Logger<T>::_writer[eLogType_Count];

    template<typename T>
    LogFormatter    Logger<T>::_formatter[eLogType_Count];

    template<typename T>
    bool_t          Logger<T>::_initialized = FALSE;
}