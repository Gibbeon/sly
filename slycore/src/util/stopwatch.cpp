#include "sly/util/stopwatch.h"
#include "sly/util/clock.h"

using namespace sly;


Stopwatch::Stopwatch() :
    _running(FALSE)
{
    reset();
}

void Stopwatch::start()
{
    _running = TRUE;
    _start = Clock::now();
}

void Stopwatch::stop()
{
    _stop = Clock::now();
    _running = FALSE;
}

TimeSpan Stopwatch::elapsed() const
{
    return TimeSpan(_start, _running ? Clock::now() : _stop); 
}

void Stopwatch::reset()
{
    _start = _stop = Clock::now();
}
