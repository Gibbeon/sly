#pragma once

#include "sly/global.h"
#include "sly/string.h"
#include "sly/math/statistics/min.h"
#include "sly/math/statistics/max.h"
#include "sly/math/statistics/average.h"
#include "sly/math/statistics/variance.h"

namespace sly {

    struct PerfResult
    {
        public:
            PerfResult();

            String<> name;
            Min<s64> min;
            Max<s64> max;
            Average<double> avg;
            Variance<double> variance;

            void print();
    };

}
