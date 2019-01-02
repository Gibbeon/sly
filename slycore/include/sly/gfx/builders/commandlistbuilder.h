#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct CommandListDesc {
        public:
        };

        class CommandListBuilder : public Builder<CommandListDesc> {
        public:
            CommandListBuilder() : Builder() {}
            virtual ~CommandListBuilder() {}
        };
    }
}