#pragma once

#include "sly/global.h"
#include "sly/util/time.h"
#include "sly/util/timespan.h"

    namespace sly {

    class Stopwatch
    {
        public:
            Stopwatch();

            void start();
            void stop();

            TimeSpan elapsed() const;
            void reset();

        private:
            Time _start;
            Time _stop;

            bool_t _running;
            
    };

}