#pragma once

#include "sly/global.h"

namespace sly {

    template<typename T>
    class vec2_t {
        public:
            vec2_t()
            {

            }

            vec2_t(T x, T y) {
                this->y = y;
                this->x = x;
            }

            //static vec2_t<T> zero = vec2_t<T>((T)0, (T)0);
            
            union {
                struct {
                    T x;
                    T y;
                };
                T a[2];
            };
    };

    typedef vec2_t<float> vec2f_t;
}
