#pragma once

#include "sly/global.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly { 
    class Resource {
    public: 
        Resource() {}
        Resource(std::shared_ptr<IDeserializer> deserializer) {
            _deserializer = deserializer;
            _deserializer->property("name").read(_name);
            _deserializer->property("type").read(_type);
        }

        template<typename T>
        retval<T> create() {      
            // this creates something dynamic, which it must by design
            // now do I know to manage

            auto object = _deserializer->create(_type.c_str());

            if(object.succeeded()) {
                T copy = *(reinterpret_cast<T*>(&object.result()));
                return copy;
            } else {
                T copy;
                ISerializable* pCopy = reinterpret_cast<ISerializable*>(&copy);
                pCopy->deserialize(*_deserializer.get());
                return copy;
            }

            return failed<T>();
        }

        const std::string& name() const { return _name; };
        const std::string& type() const { return _type; };        

    private:
        std::shared_ptr<IDeserializer> _deserializer;
        std::string _name;
        std::string _type;
    };
}



