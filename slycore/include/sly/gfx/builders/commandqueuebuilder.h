#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        
        struct CommandQueueDesc {
        public:
        };

        class CommandQueueBuilder : public Builder<CommandQueueDesc> {
        public:
            CommandQueueBuilder() : Builder() {}
            virtual ~CommandQueueBuilder() {}
        };
    }
}