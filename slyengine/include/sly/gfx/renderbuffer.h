#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    struct RenderBufferDesc {
    public:
    };

    class RenderBufferDescBuilder : public Builder<RenderBufferDesc> {
    public:
    };

    class IRenderBuffer {
    public:
    };
}