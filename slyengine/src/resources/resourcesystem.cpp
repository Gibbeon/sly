#pragma once

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/resources/builders/resourcesystem.h"
#include "sly/resources/resource.h"
#include "sly/resources/loaders/jsonresourceloader.h"
#include "sly/resources/directoryresourcerepositoryloader.h"

using namespace sly;

ResourceSystem::ResourceSystem(const Engine& engine) : _engine(engine) {}

ResourceSystem::~ResourceSystem() {}

retval<void> ResourceSystem::init(const ResourceSystemDesc& desc) {
    static DirectoryResourceRepositoryLoader loader(_engine);
    _repositoryLoaders.push_back(&loader);

    static JsonResourceLoader resLoader(_engine);
    _loaders.push_back(&resLoader);
    return success();
}

retval<void> ResourceSystem::release() {
    return success();
}

retval<void> ResourceSystem::mount(gsl::czstring<> moniker) {
    for(auto loader : _repositoryLoaders) {
        if(loader->supports(moniker)) {
            _repositories.push_back(loader->open(moniker).result());
            return success();
        }
    }
    return failed<void>();
}

retval<void> ResourceSystem::unmount(gsl::czstring<> moniker) {
    for (auto repo = _repositories.begin(); repo < _repositories.end(); repo++) {
        if((*repo)->moniker() == moniker) {
            auto result = (*repo)->close();
            if(result.failed()) {
                return failed();
            }

            _repositories.erase(repo);
        }
    }

    return success();
}

retval<Resource> ResourceSystem::find(gsl::czstring<> moniker) {
    for(auto repo : _repositories) {
        for(auto& value : repo->resources()) {
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




