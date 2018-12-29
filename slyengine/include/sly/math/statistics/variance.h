#pragma once


#include "sly/global.h"

namespace sly {

    template <typename T = s32>
    class Variance
    {
        public:
            Variance();
            Variance(T value, T mean, s32 count);
            Variance(const Variance& copy);

            void accumulate(T value);
            Variance& operator=(Variance& rhs);
            Variance& operator+=(T value);

            operator T() const;
            T operator*() const;
            
            T value() const;
            s32 count() const;
            T stddev() const;
            bool_t isDefined() const;

            static Variance calculate(Enumerable<T> array);

        private:
            s32 count_;
            T mean_;
            T value_;
    };

    #include "sly/math/statistics/variance.hpp"

}
