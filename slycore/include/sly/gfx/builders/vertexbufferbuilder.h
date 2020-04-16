#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/inputelement.h"
#include "sly/gfx/builders/resourcebuilder.h" 

namespace sly {
    namespace gfx {
        ENUM_DECL(eBufferType,
            eBufferType_Vertex,
            eBufferType_Index
        );

        struct BufferDesc : public ISerializable {
        public:
            SLY_TYPEINFO;
                        
            std::string                     name;
            eBufferType                     bufferType;   

            std::vector<InputElementDesc>   descriptors;
            
            size_t stride;
            size_t count;
            size_t sizeInBytes;
            std::shared_ptr<byte_t> data;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                //archive.begin(*this, name);
                
                archive.write("name", name);        
                
                //archive.end();

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                DESERIALIZE(name);      
                DESERIALIZE(count);      
                DESERIALIZE(sizeInBytes);              
                DESERIALIZE(bufferType, eBufferType_Vertex);

                size_t offset = 0;
                {
                    auto& __array = archive.open("descriptors");
                    gfx::InputElementDesc __desc;
                    for(size_t i = 0; i < __array.size(); i++) {
                        __array[i].read(__desc);
                        __desc.offset  = offset;
                        offset         += __desc.size;
                        descriptors.push_back(__desc);
                    }
                    __array.close();
                }
                
                DESERIALIZE(stride, offset);

                {
                    auto& __array = archive.open("data");
                    count       = count ? count : __array.size();
                    sizeInBytes = align<256>(sizeInBytes ? sizeInBytes : (count * stride));

                    Expects(__array.size() == count);
                    Expects(sizeInBytes >= count * stride);
                    
                    data = std::shared_ptr<byte_t>(new byte_t[sizeInBytes], std::default_delete<byte_t[]>());
                    byte_t* ptr = data.get();

                    for(size_t i = 0; i < __array.size(); i++) {
                        auto& vertex = __array[i];
                        for(auto& descriptor : descriptors) {
                            auto& element = vertex.property(descriptor.semanticName.c_str());
                            // how to know if the property is empty                   
                            
                            switch(descriptor.format) {
                                case eDataFormat_R32G32B32_FLOAT:
                                    element.read<f32>(ptr, 3);
                                    break;
                                case eDataFormat_R32G32B32A32_FLOAT:
                                    element.read<f32>(ptr, 4);
                                    break;
                                case eDataFormat_R8G8B8A8_UNORM:
                                    element.read<u8>(ptr, 4);
                                    break;
                            }

                            Expects(descriptor.size > 0);
                            Expects(descriptor.size >= gfx::sizeOf(descriptor.format));

                            ptr += descriptor.size;
                            element.close();
                        }
                        vertex.close();                        
                    }
                    __array.close();
                }

                return sly::success();
            }    
        };

        class BufferBuilder : public Builder<BufferDesc> {
        public:
            BufferBuilder() : Builder() {}        
            virtual ~BufferBuilder() {}

             BufferBuilder& setType(eBufferType type) { 
                ////_descriptor.type = type;
                return *this; 
            }

            BufferBuilder& setData(vptr_t data, size_t sizeInBytes, size_t stride) { 
                //_descriptor.data = (f32*)data;
                //_descriptor.stride = stride;  
                //_descriptor.sizeInBytes = sizeInBytes; 
                return *this; 
            }
        };
        
        /*struct VertexBufferDesc : public BufferDesc {
        public:

        };


        //class VertexBufferBuilder : public Builder<VertexBufferDesc> {
        public:
            VertexBufferBuilder() : Builder() {
                _descriptor.count = 0;
                _descriptor.type = eBufferType_Vertex;
            }            
            virtual ~VertexBufferBuilder() {}

            VertexBufferBuilder& setData(vptr_t data, size_t count, size_t stride) { 
                _descriptor.data.reset((uint_t*)data); 
                _descriptor.count = count; 
                _descriptor.stride = (size_t)stride;  
                _descriptor.sizeInBytes = (size_t)count * stride; 
                return * this; 
            }
        };*/
    }
}

