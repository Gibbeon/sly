#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {
        struct RenderTargetDesc {
        public:
        };

        class RenderTargetBuilder : public Builder<RenderTargetDesc> {
        public:
            RenderTargetBuilder() : Builder() {}
            virtual ~RenderTargetBuilder() {}
        };
    }
}

