#pragma once

#include "sly/global.h"

namespace sly { 
    class Resource;
    class IResourceRepository;
    struct ResourceHandle;

    class IResourceLoader {
    public:
        virtual retval<void> release() = 0;

        virtual bool_t supports(ResourceHandle& handle) = 0;
        virtual retval<std::vector<Resource>> load(IResourceRepository& repo, ResourceHandle& handle) = 0;
    };
}



