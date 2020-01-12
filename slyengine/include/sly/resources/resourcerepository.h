#pragma once

#include "sly/global.h"

namespace sly { 
    class IInputStream;
    struct ResourceHandle;
    
    class IResourceRepository {
    public:
        virtual ~IResourceRepository() {}
        //virtual retval<void> init(const ResourceSystemDesc& desc = ResourceSystemBuilder().build());
        virtual retval<void> release() = 0;
        
        virtual retval<void> open(gsl::czstring<> moniker) = 0;
        virtual retval<void> close() = 0;

        virtual retval<IInputStream&> getStream(ResourceHandle&) = 0;

        virtual std::vector<ResourceHandle> resources() const = 0;
    protected:
        IResourceRepository() {}
    };        
}



