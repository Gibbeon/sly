#include "sly/util/stopwatch.h"
#include "sly/util/clock.h"

using namespace sly;


Stopwatch::Stopwatch() :
    running_(FALSE)
{
    reset();
}

void Stopwatch::start()
{
    running_ = TRUE;
    start_ = Clock::now();
}

void Stopwatch::stop()
{
    stop_ = Clock::now();
    running_ = FALSE;
}

TimeSpan Stopwatch::elapsed() const
{
    return TimeSpan(start_, running_ ? Clock::now() : stop_); 
}

void Stopwatch::reset()
{
    start_ = stop_ = Clock::now();
}
