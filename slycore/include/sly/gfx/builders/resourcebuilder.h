#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/runtime/serializable.h"

namespace sly {
    namespace gfx {
        struct ResourceDesc : public virtual sly::ISerializable {
        public:
            SLY_TYPEINFO;

            std::string name;
            
            uint_t sizeInBytes;
            uint_t stride;

            f32* data;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                //archive.begin(*this, name);
                
                archive.write("name", name);        
                
                //archive.end();

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                archive.read("name", name);
                archive.read("sizeInBytes", sizeInBytes);
                archive.read("stride", stride);

                data = (f32*)malloc(sizeInBytes);

                auto array = archive.array("data");
                for(size_t i = 0; i < array->size(); i++) {
                    f32 item;
                    array->read(i, item);
                    data[i] = item;
                }

                return sly::success();
            }
        };

        class ResourceBuilder : public Builder<ResourceDesc> {
        public:
            ResourceBuilder() : Builder() {}        
            virtual ~ResourceBuilder() {}
            
            ResourceBuilder& setSizeInBytes(size_t size) { _descriptor.sizeInBytes = size; return * this; }
        };
    }
}
