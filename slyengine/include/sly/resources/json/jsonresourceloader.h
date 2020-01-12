#pragma once

#include "sly/global.h"
#include "sly/resources/resourceloader.h"
#include "sly/resources/resourcerepository.h"
#include "sly/resources/resourcehandle.h"
#include "sly/resources/json/jsondeserializer.h"


namespace sly { 
    class JsonResourceLoader : public IResourceLoader {
    public:
        virtual retval<void> release() {
            return success();
        }

        virtual bool_t supports(ResourceHandle& handle) {  
            return handle.extension == ".json";
        }

        virtual retval<Resource> load(IResourceRepository& repo, ResourceHandle& handle) {
            auto stream = repo.getStream(handle);
            sly::IInputStream& result = stream.result();
            return Resource(new JsonDeserializer(result));           
        }

    private:
    
    };
}



