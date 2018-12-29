#pragma once

#include "sly/global.h"

namespace sly {

    template <typename T = s32>
    class Min {
    public:
        Min();
        Min(T value);
        Min(const Min& copy);

        void accumulate(T value);
        Min& operator=(Min& rhs);
        Min& operator+=(T value);

        operator T() const;
        T operator*() const;
                
        T value() const;
        bool_t isDefined() const;

        static Min calculate(Enumerable<T> array);

    private:
        T value_;
        bool_t assigned_;
    };

    #include "sly/math/statistics/min.hpp"

}
