#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct WindowDesc {
        public:
        };

        class WindowBuilder : public Builder<WindowDesc> {
        public:
            WindowBuilder() : Builder() {}
            virtual ~WindowBuilder() {}
            
        };
    }
}