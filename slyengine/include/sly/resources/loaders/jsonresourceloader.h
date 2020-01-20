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

        virtual retval<std::vector<Resource>> load(IResourceRepository& repo, ResourceHandle& handle) {
            auto stream = repo.getStream(handle);
            auto& value = *(stream.result());
            auto derserializer = JsonDeserializer(value);
            
            auto result = std::vector<Resource>();
            result.reserve(derserializer.size());

            if(derserializer.size() > 1) {
                for(auto elem : derserializer.data()) {                    
                   result.push_back(Resource(std::make_shared<JsonDeserializer>(elem)));
                }
            } else {
                result.push_back(Resource(std::make_shared<JsonDeserializer>(derserializer.data())));
            }

            return result;           
        }

    private:
        const Engine& _engine;
    
    };
}



