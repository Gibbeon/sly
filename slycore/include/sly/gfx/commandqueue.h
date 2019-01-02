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
            CommandQueueBuilder() : Builder({}) {}
        };

        class ICommandList;
        class ICommandQueue {
        public:
            
            virtual void init(CommandQueueDesc& desc) = 0;
            virtual void executeCommandList(ICommandList* lists, size_t count = 1) = 0;
        };
    }
}