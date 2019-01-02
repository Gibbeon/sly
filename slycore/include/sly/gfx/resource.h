#pragma once

#include "sly/global.h"
#include "sly/gfx/managedresource.h"
#include "sly/gfx/builders/resourcebuilder.h"

namespace sly {
    namespace gfx {       

        class IResource : public IManagedResource  {
        public:
            virtual ~IResource() {}
            //virtual void init(ResourceDesc& desc) = 0;

            virtual void write(vptr_t data, size_t size, size_t stride) = 0;
        protected:
            IResource() {}
        };
    }
}