#pragma once

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/resources/resourcerepositoryloader.h"
#include "sly/resources/directoryresourcerepository.h"

namespace sly { 
    class DirectoryResourceRepositoryLoader : public IResourceRepositoryLoader {
    public:
        DirectoryResourceRepositoryLoader(const Engine& engine) : _engine(engine) {

        }

        virtual retval<void> release() {
            return success(); 
        }
        
        virtual bool_t supports(gsl::czstring<> moniker) {
             struct stat fileInfo;
             stat(moniker, &fileInfo);

             return((fileInfo.st_mode & _S_IFDIR) == _S_IFDIR);
        }

        virtual retval<std::shared_ptr<IResourceRepository>> open(gsl::czstring<> moniker) {
            auto load = std::make_shared<DirectoryResourceRepository>(_engine);

            if(load->open(moniker).failed()) {
                return failed<std::shared_ptr<IResourceRepository>>();
            }

            return load;
        }

        virtual retval<void>                close(IResourceRepository& repository) {   
            return repository.close();
        }

    protected:
        const Engine& _engine;
    };
}



