#pragma once

#include "sly/global.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly { 
    class ISerializable {
    public:
        virtual ~ISerializable() {}
        //virtual gsl::czstring<> getType() const = 0;
        //virtual gsl::czstring<> getName() const = 0;

        virtual retval<void> serialize(IDeserializer& archive) = 0;
        virtual retval<void> deserialize(IDeserializer& archive) = 0;
    
    protected:
        ISerializable() {}
    };

    struct ShaderDesc2 : public ISerializable {
    public:
        vptr_t data;
        size_t size;
        std::string entry;
        std::string target;
        std::string name;
 
        retval<void> serialize(IDeserializer& archive) {
            //auto record = archive.new(name, *this);

            return success();
        }

        retval<void> deserialize(IDeserializer& archive) {
            //auto record = archive.read();
            //data = archive.get("data");
            //size = archive.getInteger("size");
            archive.read("entryPoint", entry);
            archive.read("target", target);
            archive.read("name", name);
            //archive >> std::make_tuple("name", name);

            return success();
        }
    };
}



