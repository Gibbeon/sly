#pragma once

#include "sly/global.h"

namespace sly {

    template<typename T>
    class rectt_t {
        public:
            rectt_t()
            {

            }

            rectt_t(T left, T top, T right, T bottom) {
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

    typedef rectt_t<float> box_t;
    typedef rectt_t<size_t> rect_t;
}
