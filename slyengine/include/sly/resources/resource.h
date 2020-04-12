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

        retval<std::shared_ptr<ISerializable>> create() { 
            std::shared_ptr<ISerializable> result;
            auto object = _deserializer->create(_type.c_str());
            if(object.succeeded()) {
                result.reset(reinterpret_cast<ISerializable*>(&object.result()));
                return result;
            }
            return failed<std::shared_ptr<ISerializable>>();
        }

        template<typename T>
        retval<void> create(T& out) {      
            // this object would have had to be created dynamically
            auto object = _deserializer->create(_type.c_str());

            if(object.succeeded()) {
                out = *(reinterpret_cast<T*>(&object.result()));

                return success();
            } else {
                out.deserialize(*_deserializer.get());
                return success();
            }

            return failed();
        }

        template<typename T>
        retval<std::shared_ptr<T>> create() {      
            std::shared_ptr<T> result;

            auto object = _deserializer->create(_type.c_str());            

            if(object.succeeded()) {
                auto& value = object.result();
                result.reset(reinterpret_cast<T*>(&value));
                return result;
            } else {
                if(TypeInfo::get<T>().name() == _type) {
                    result = std::make_shared<T>();
                    result->deserialize(*_deserializer.get());
                    return result;
                }

                return failed<std::shared_ptr<T>>();
            }

            return failed<std::shared_ptr<T>>();
        }

        const std::string& name() const { return _name; };
        const std::string& type() const { return _type; };        

    private:
        std::shared_ptr<IDeserializer> _deserializer;
        std::string _name;
        std::string _type;
    };
}



