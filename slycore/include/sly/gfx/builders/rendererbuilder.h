#pragma once

#include "sly/global.h"
#include "sly/builder.h"

// this is actually a plugin, ignoring for now

namespace sly {
    namespace gfx {
        struct RendererDesc {
        public:
        };

        class RendererBuilder : public Builder<RendererDesc> {
        public:
            RendererBuilder() : Builder() {}
        };
    }
}