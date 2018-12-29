#pragma once

#include "sly/global.h"
#include <xmmintrin.h>
#include <cmath>

namespace sly {

    class Math
    {
        public:
            template <typename T>
            static inline T min(T lhs, T rhs);

            template <typename T>
            static inline T max(T lhs, T rhs);

            static inline float sqrt(float x);
            static inline float sqrt_appx(float x);

            static inline float rsqrt(float x);
            static inline float rsqrt_appx(float x);
    };

    #include "sly/math/math.hpp"
    
}
