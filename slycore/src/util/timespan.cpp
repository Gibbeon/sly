#include "sly/util/timespan.h"

using namespace sly;


TimeSpan::TimeSpan(Time start, Time end)
{
    _ticks = end.getNanoseconds() - start.getNanoseconds();
}

s64 TimeSpan::getNanoseconds() const
{
    return _ticks;
}
