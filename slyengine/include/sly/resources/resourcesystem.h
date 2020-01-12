#pragma once

#include "sly/global.h"
#include "sly/resources/builders/resourcesystem.h"
#include "sly/resources/resource.h"
#include "sly/resources/json/jsonresourceloader.h"
#include "sly/resources/directoryresourcerepositoryloader.h"

namespace sly { 
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
        virtual retval<void> init(const ResourceSystemDesc& desc = ResourceSystemBuilder().build()) {
            static DirectoryResourceRepositoryLoader loader;
            _repositoryLoaders.push_back(&loader);

            static JsonResourceLoader resLoader;
            _loaders.push_back(&resLoader);
            return success();
        }

        virtual retval<void> release() {
            return success();
        }

        virtual retval<void> mount(gsl::czstring<> moniker) {
            for(auto loader : _repositoryLoaders) {
                if(loader->supports(moniker)) {
                    _repositories.push_back(loader->open(moniker).result());
                    return success();
                }
            }
            return failed<void>();
        }

        virtual retval<void> unmount(gsl::czstring<> moniker) {

            return success();
        }

        virtual retval<Resource> find(gsl::czstring<> moniker) {
            for(auto repo : _repositories) {
                for(auto value : repo->resources()) {
                    if(value.moniker == moniker) {
                        for(auto loader: _loaders) {
                            if(loader->supports(value)) {
                                return loader->load(*repo, value);
                            }
                        }
                    }
                }
            }

            return failed<Resource>();
        }
    
    protected:
        std::vector<IResourceRepositoryLoader*>                     _repositoryLoaders;
        std::vector<IResourceLoader*>                               _loaders;
        std::vector<std::shared_ptr<IResourceRepository>>           _repositories;
    };
}



