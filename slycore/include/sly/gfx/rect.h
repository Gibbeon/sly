#pragma once

#include "sly/global.h"

namespace sly {

    template<typename T>
    class rect_t {
        public:
            rect_t()
            {

            }

            rect_t(T left, T top, T right, T bottom) {
                this->left = left;
                this->top = top;
                this->right = right;
                this->bottom = bottom;
            }

            //static rect_t zero = vec4_t((T)0, (T)0, (T)0, (T)0);
            
            union {
                struct {
                    T left;
                    T top;
                    T right;
                    T bottom;
                };
                T a[4];
            };
    };

    typedef rect_t<float> rectf_t;
    typedef rect_t<u32> recti_t;
}
