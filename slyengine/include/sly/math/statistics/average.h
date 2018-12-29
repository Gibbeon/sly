#pragma once

#include "sly/global.h"

namespace sly {

    template <typename T = s32>
    class Average
    {
        public:
            Average();
            Average(T value, s32 count);
            Average(const Average& copy);

            void accumulate(T value);
            Average& operator=(Average& rhs);
            Average& operator+=(T value);

            operator T() const;
            T operator*() const;
                    
            T value() const;
            s32 count() const;
            bool_t isDefined() const;

            static Average calculate(Enumerable<T> array);

        private:
            T value_;
            s32 count_;
    };

    #include "sly/math/statistics/average.hpp"
}
