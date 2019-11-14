#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct RenderContextDesc {
        public:
        };

        class RenderContextBuilder : public Builder<RenderContextDesc> {
        public:
            RenderContextBuilder() : Builder() {}
            virtual ~RenderContextBuilder() {}
            
        };
    }
}