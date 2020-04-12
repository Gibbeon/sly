#pragma once

#include "sly/global.h"
#include "sly/resources/resourceloader.h"
#include "sly/resources/resourcerepository.h"
#include "sly/resources/resourcehandle.h"
#include "sly/runtime/serialization/json/jsondeserializer.h"


namespace sly { 
    class JsonResourceLoader : public IResourceLoader {
    public:
        JsonResourceLoader(const Engine& engine) : _engine(engine) {}
        virtual retval<void> release() {
            return success();
        }

        virtual bool_t supports(ResourceHandle& handle) {  
            return handle.extension == ".json";
        }

        virtual retval<Resource> load(IResourceRepository& repo, ResourceHandle& handle) {
            auto stream = repo.getStream(handle);
            auto value = std::make_shared<JsonDeserializer>(*stream.result().get(), _engine.activator());
            return Resource(value);           
        }

    private:
        const Engine& _engine;
    
    };
}



