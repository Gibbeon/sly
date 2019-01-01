#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        template<typename TColorType = float>
        struct color_t
        {
            color_t(TColorType r, TColorType g, TColorType b, TColorType a) :
                r(r), g(g), b(b), a(a)
            {

            }
            union {
                struct {
                    TColorType r;
                    TColorType g;
                    TColorType b;
                    TColorType a;
                };                
                TColorType data[4];
            };
        };
    }
}

