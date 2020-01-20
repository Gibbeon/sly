#pragma once

#include "sly/global.h"
#include "sly/gfx/managedresource.h"
#include "sly/gfx/builders/resourcebuilder.h"

namespace sly {
    namespace gfx {       

        class IResource : public virtual IManagedResource  {
        public:
            virtual ~IResource() {}
            virtual retval<void> release() = 0;
            //virtual void init(Resource& desc) = 0;

            //virtual void write(vptr_t data, size_t size, size_t stride) = 0;
        protected:
            IResource() {}
        };
    }
}