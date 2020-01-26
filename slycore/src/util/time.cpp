#include <time.h>
#include <ctime>

#include "sly/util/time.h"

#define     HAS_UNCAUGHT_EXCEPTIONS 1
#include    "date/date.h"
#undef      HAS_UNCAUGHT_EXCEPTIONS

using namespace sly;


Time::Time() :
    Time(0)
{

}

Time::Time(s64 nanoseconds) :
    _ticks(nanoseconds)
{
}

s64 Time::getNanoseconds() const
{   
    return _ticks;
}


std::string Time::toString(gsl::czstring<> fmt)      
{
    return date::format(fmt, std::chrono::nanoseconds(_ticks));
    
    //time_t rawtime = time(&_ticks);
    //struct tm timeinfo;
    //char buffer[80];

    //localtime_s(&timeinfo, &rawtime);

    //strftime(buffer,sizeof(buffer), fmt, &timeinfo);
    //return buffer;
}    