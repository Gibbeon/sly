#include "sly/util/time.h"

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
