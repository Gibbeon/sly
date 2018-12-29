#include "sly/util/timespan.h"

using namespace sly;


TimeSpan::TimeSpan(Time start, Time end)
{
    ticks_ = end.getNanoseconds() - start.getNanoseconds();
}

s64 TimeSpan::getNanoseconds() const
{
    return ticks_;
}
