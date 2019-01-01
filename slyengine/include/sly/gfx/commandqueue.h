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
            virtual void executeCommandList(ref_t<ICommandList> list) = 0;

        protected:
            constexpr static CommandQueueDesc DEFAULT = {  }; 
        };
    }
}