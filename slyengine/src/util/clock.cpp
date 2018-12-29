#include "sly/util/clock.h"

#include <chrono>

using namespace sly;


Time Clock::now()
{
    auto a = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now());
    auto b = a.time_since_epoch();
    return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(b).count());
}