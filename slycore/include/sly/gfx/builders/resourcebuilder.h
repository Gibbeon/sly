#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/runtime/serializable.h"

namespace sly {
    namespace gfx {
        //eBufferDataType_Float

        struct ResourceDesc : public sly::ISerializable {
        public:
            SLY_TYPEINFO;

            std::string name;
            
            size_t stride;
            size_t count;
            size_t sizeInBytes;

            std::shared_ptr<byte_t[]> data;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                //archive.begin(*this, name);
                
                archive.write("name", name);        
                
                //archive.end();

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                DESERIALIZE(name);
                DESERIALIZE(stride, sizeof(f32));                
                DESERIALIZE(count);
                DESERIALIZE(sizeInBytes);

                /*{
                    auto& __array = archive.open("array");
                    count       = count ? count : __array.size();
                    sizeInBytes = sizeInBytes ? sizeInBytes : (count * stride);

                    Expects(__array.size() == count);
                    Expects(sizeInBytes == count);
                    
                    data = std::make_shared<byte_t>(new byte_t[sizeInBytes], std::default_delete<byte_t[]>());
                    for(size_t i = 0; i < __array.size(); i++) {
                        __array[i].read(((f32*)data.get())[i]);
                    }
                    __array.close();
                }*/

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
