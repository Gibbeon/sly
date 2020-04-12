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
            auto string = TextReader(value).readAll();
            auto derserializer = JsonDeserializer(string, _engine.activator());
            
            auto result = std::vector<Resource>();
            result.reserve(derserializer.size());

            if(derserializer.size() > 1) {
                for(auto& elem : derserializer.data()) {                    
                   result.push_back(Resource(std::make_shared<JsonDeserializer>(elem, _engine.activator())));
                }
            } else {
                result.push_back(Resource(std::make_shared<JsonDeserializer>(derserializer.data(), _engine.activator())));
            }

            return result;           
        }

    private:
        const Engine& _engine;
    
    };
}



