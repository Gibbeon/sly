#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        struct Viewport
        {
            Viewport(real_t x, real_t y, real_t width, real_t height, real_t minDepth = real_t(0.0), real_t maxDepth = real_t(1.0)) :
                x(x), y(y), width(width), height(height), minDepth(minDepth), maxDepth(maxDepth)
            {

            }
            real_t x;
            real_t y;
            real_t width;
            real_t height;
            real_t minDepth;
            real_t maxDepth;
        };
    }
}

