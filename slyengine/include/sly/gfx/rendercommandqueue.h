#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/collections/array.h"

namespace sly {
    
    struct RenderCommandQueueDesc {
    public:
    };

    class RenderCommandQueueDescBuilder : public Builder<RenderCommandQueueDesc> {
    public:
    };

    class IRenderCommandList;
    class IRenderCommandQueue {
    public:
        void ExecuteCommandList(Array<IRenderCommandList*>& lists);
    };

}