#pragma once

#include "sly/global.h"
#include "sly/resources/deserializer.h"

namespace sly { 
    class Resource {
    public: 
        Resource() {}
        Resource(IDeserializer* deserializer) :
            _deserializer(deserializer) {

        }

        template<typename T>
        retval<std::shared_ptr<T>> get(gsl::czstring<> moniker) {            
            auto result = std::make_shared<T>();
            _deserializer->readObject(moniker, *result.get());
            return result;
        }

    private:
        IDeserializer* _deserializer;
    };
}



