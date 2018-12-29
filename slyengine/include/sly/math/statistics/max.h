#pragma once

#include "sly/global.h"

namespace sly {

    template <typename T = s32>
    class Max
    {
        public:
            Max();
            Max(T value);
            Max(const Max& copy);

            void accumulate(T value);
            Max& operator=(Max& rhs);
            Max& operator+=(T value);

            operator T() const;
            T operator*() const;
                    
            T value() const;
            bool_t isDefined() const;

            static Max calculate(Enumerable<T> array);

        private:
            T value_;
            bool_t assigned_;
    };

    #include "sly/math/statistics/max.hpp"

}
