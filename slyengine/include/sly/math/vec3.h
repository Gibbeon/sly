#pragma once

#include "sly/global.h"

namespace sly {

    template<typename T = float>
    class vec3_t {
    public:
        vec3_t()
        {

        }

        vec3_t(T x, T y, T z) {
            this->y = y;
            this->x = x;
            this->z = z;
        }

        //static vec3_t zero = vec3_t((T)0, (T)0, (T)0);
        
        union {
            struct {
                T x;
                T y;
                T z;
            };
            T data[3];
        };
    };
}
