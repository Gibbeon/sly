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

            virtual retval<void> init(const CommandQueueDesc& desc) = 0;
            virtual retval<void> release() = 0;
            
            virtual void executeCommandList(gsl::span<const ICommandList* const> lists) = 0;

            virtual void flush() = 0;
        protected:
            ICommandQueue() {}
        };
    }
}