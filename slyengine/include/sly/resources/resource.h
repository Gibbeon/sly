#pragma once

#include "sly/global.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly { 
    class Resource {
    public: 
        Resource() {}

        Resource(std::shared_ptr<IDeserializer> deserializer) :
            _deserializer(deserializer) {
            _deserializer->property("name").read(_name);
            _deserializer->property("type").read(_type);
        }

        template<typename T>
        retval<std::shared_ptr<T>> create() {            
            auto result = std::make_shared<T>();
            _deserializer->read(*result.get());
            return result;
        }

        const std::string& name() const { return _name; };
        const std::string& type() const { return _type; };        

    private:
        std::shared_ptr<IDeserializer> _deserializer;
        std::string _name;
        std::string _type;
    };
}



