#pragma once

#include "sly/global.h"

namespace sly {

    template<typename T>
    class vec4_t {
        public:
            vec4_t()
            {

            }

            vec4_t(T x, T y, T z, T w) {
                this->y = y;
                this->x = x;
                this->z = z;
                this->w = w;
            }

            static vec4_t zero = vec4_t((T)0, (T)0, (T)0, (T)0);
            
            union {
                struct {
                    T x;
                    T y;
                    T z;
                    T w;
                };
                T a[4];
            };
    };

    typedef vec4_t<float> vec4f_t;
}
