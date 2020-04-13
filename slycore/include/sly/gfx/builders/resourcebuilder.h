#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/runtime/serializable.h"

namespace sly {
    namespace gfx {
        //eBufferDataType_Float

        struct ResourceDesc : public virtual sly::ISerializable {
        public:
            SLY_TYPEINFO;

            std::string name;
            
            size_t stride;
            size_t count;
            size_t sizeInBytes;

            vptr_t data;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                //archive.begin(*this, name);
                
                archive.write("name", name);        
                
                //archive.end();

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                archive.property("name").read(name);
                archive.property("stride").read(stride);

                auto& array = archive.open("array");

                for(size_t i = 0; i < array.size(); i++) {
                    f32 item;
                    array.at(i).read(item);
                    //data[i] = item;
                }
                array.close();

                return sly::success();
            }
        };

        class ResourceBuilder : public Builder<ResourceDesc> {
        public:
            ResourceBuilder() : Builder() {}        
            virtual ~ResourceBuilder() {}
            
            //ResourceBuilder& setSizeInBytes(size_t size) { _descriptor.sizeInBytes = size; return * this; }
        };
    }
}
