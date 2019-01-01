#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        struct Viewport
        {
            Viewport(float x, float y, float width, float height, float minDepth = 0.0, float maxDepth = 1.0) :
                x(x), y(y), width(width), height(height), minDepth(minDepth), maxDepth(maxDepth)
            {

            }
            float x;
            float y;
            float width;
            float height;
            float minDepth;
            float maxDepth;
        };
    }
}

