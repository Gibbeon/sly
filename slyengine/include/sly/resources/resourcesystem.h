#pragma once

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/resources/resource.h"
#include "sly/resources/builders/resourcesystem.h"

namespace sly { 
    class Engine;
    class IResourceRepositoryLoader;
    class IResourceLoader;
    class IResourceRepository;

    class IResourceSystem {
    public:
        virtual ~IResourceSystem() {}

        virtual retval<void> init(const ResourceSystemDesc&) = 0;
        virtual retval<void> release() = 0;

        virtual retval<void> mount(gsl::czstring<> moniker) = 0;
        virtual retval<void> unmount(gsl::czstring<> moniker) = 0;
        virtual retval<Resource> find(gsl::czstring<> moniker) = 0;

    protected:
        IResourceSystem() {}
    };

   
    class ResourceSystem : public IResourceSystem {
    public:
        ResourceSystem(const Engine& engine);
        virtual ~ResourceSystem();

        virtual retval<void> init(const ResourceSystemDesc& desc = ResourceSystemBuilder().build());
        virtual retval<void> release();

        virtual retval<void> mount(gsl::czstring<> moniker);
        virtual retval<void> unmount(gsl::czstring<> moniker);

        virtual retval<Resource> find(gsl::czstring<> moniker);
    
    protected:
        const Engine& _engine;

        std::vector<IResourceRepositoryLoader*>                     _repositoryLoaders;
        std::vector<IResourceLoader*>                               _loaders;
        std::vector<std::shared_ptr<IResourceRepository>>           _repositories;
    };
}



