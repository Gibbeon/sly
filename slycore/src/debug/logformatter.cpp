#pragma once

#include <vector>
#include <functional>
#include <sstream>
#include <iomanip>

#include "sly/debug/logformatter.h"
#include "sly/util/time.h"
#include "sly/util/thread.h"


using namespace sly;

LogFormatter::LogFormatter() : _initialized(FALSE) {

}

void LogFormatter::writeTimestamp(LogMessage& msg, std::ostringstream& ostream) {

    ostream << sly::Clock::now().toString("%T").c_str();
    ostream << "|";
}

void LogFormatter::init() {
    if(!_initialized) {        
        static std::mutex mutex;
        std::scoped_lock lock(mutex);
        if(!_initialized) {
            _prepend.push_back(&writeLevel);
            _prepend.push_back(&writeTimestamp);
            _prepend.push_back(&writeThreadName);
            _formatter = &writeMessage;
            _append.push_back([](LogMessage& msg, std::ostringstream& ostream) { ostream << " | at "; });
            _append.push_back(&writeLineClass);
            _initialized = true;
        }
    }
}

void LogFormatter::writeThreadId(LogMessage& msg, std::ostringstream& ostream) {

    ostream << std::this_thread::get_id();
    ostream << "|";
}

void LogFormatter::writeThreadName(LogMessage& msg, std::ostringstream& ostream) {
    ostream << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(20);

    ostream << sly::Thread::name();
    ostream << " (";
    ostream << std::setfill(' ') << std::setw(5);
    ostream << std::this_thread::get_id();
    ostream << ")|";

    ostream << std::resetiosflags(std::ios::showbase );
}


void LogFormatter::writeLevel(LogMessage& msg, std::ostringstream& ostream) {


    switch(msg.level) {
        case eLogLevel_Verbose:
        ostream << "INFO ";
        break;
        case eLogLevel_Debug:
        ostream << "DEBUG";
        break;
        case eLogLevel_Warning:
        ostream << "WARN ";
        break;
        case eLogLevel_Error:
        ostream << "ERROR";
        break;
    }

    ostream << "|";
}

void LogFormatter::writeMessage(LogMessage& msg, std::ostringstream& ostream) {
    char_t buffer[1024];
    std::vsnprintf(buffer, 1024, msg.fmt, msg.args);    

    ostream << " " << buffer;
}

void LogFormatter::writeLineClass(LogMessage& msg, std::ostringstream& ostream) {
    ostream << msg.cls;
    ostream << ":";
    ostream << msg.line;
    ostream << std::endl;
}

std::string LogFormatter::format(eLogType type, eLogLevel level, gsl::czstring<> cls, gsl::czstring<> line, gsl::czstring<> fmt, va_list args) {
    std::ostringstream stringStream;
    LogMessage msg = {type, level, cls, line, fmt, args};

    for(auto& fn : _prepend) {
        fn(msg, stringStream);
    }

    _formatter(msg, stringStream);            

    for(auto& fn : _append) {
        fn(msg, stringStream);
    } 

    return stringStream.str();
}