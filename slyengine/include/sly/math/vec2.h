#pragma once

#include "sly/global.h"

namespace sly {

    template<typename T = float>
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
            T data[2];
        };
    };
}
