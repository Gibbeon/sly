#pragma once

#include "sly/global.h"
#include "sly/gfx/managedresource.h"
#include "sly/gfx/builders/commandqueuebuilder.h"

namespace sly {
    namespace gfx {
        class ICommandList;
        class ICommandQueue : public IManagedResource  {
        public:         
            virtual ~ICommandQueue() {}

            virtual void init(CommandQueueDesc& desc) = 0;
            virtual void executeCommandList(ICommandList* lists, size_t count = 1) = 0;
        protected:
            ICommandQueue() {}
        };
    }
}