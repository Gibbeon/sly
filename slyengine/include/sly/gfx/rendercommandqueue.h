#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/collections/array.h"

namespace sly {
    namespace gfx {
        
        struct CommandQueueDesc {
        public:
        };

        class CommandQueueBuilder : public Builder<CommandQueueDesc> {
        public:
        };

        class ICommandList;
        class ICommandQueue {
        public:
            void executeCommandList(Array<ICommandList>& lists);
        };
    }
}