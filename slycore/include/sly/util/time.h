#pragma once

#include "sly/global.h"

namespace sly {
    class Time
    {
        public:
            Time();
            Time(s64 ticks_);

            s32 getHour() const;
            s32 getMinute() const;
            s32 getSeconds() const;
            s64 getMilliseconds() const;
            s64 getNanoseconds() const;

        private:
            s64 _ticks;
    };
}