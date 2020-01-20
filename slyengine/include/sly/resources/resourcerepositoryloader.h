#pragma once

#include "sly/global.h"

namespace sly { 
    class IResourceRepository;
    class IResourceRepositoryLoader {
    public:
        virtual retval<void> release() = 0;
        
        virtual bool_t supports(gsl::czstring<> moniker) = 0;
        virtual retval<std::shared_ptr<IResourceRepository>> open(gsl::czstring<> moniker) = 0;
        virtual retval<void>                close(IResourceRepository& repository) = 0;
    };
}



