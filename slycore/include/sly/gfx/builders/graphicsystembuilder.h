#pragma once

#include "sly/global.h"
#include "sly/builder.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {
        struct GraphicSystemDesc {

        };

        class GraphicSystemBuilder : public Builder<GraphicSystemDesc> {
        public:
            GraphicSystemBuilder() : Builder() {}
        };
    }
}