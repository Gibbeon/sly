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
            byte_t* data;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                //archive.begin(*this, name);
                
                archive.write("name", name);        
                
                //archive.end();

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                archive.property("name").read(name);       
                archive.property("bufferType").read(bufferType, eBufferType_Vertex);

                size_t offset = 0;
                auto& elementsArray = archive.open("descriptors");
                for(size_t i = 0; i < elementsArray.size(); i++) {
                    gfx::InputElementDesc element;
                    elementsArray.at(i).read(element);

                    element.offset  = offset;
                    offset          += element.size;

                    descriptors.push_back(element);
                }
                elementsArray.close();
                
                archive.property("stride").read(stride, offset);
                archive.property("count").read(count);      
                archive.property("sizeInBytes").read(sizeInBytes); 

                auto& dataArray = archive.open("data");
                if(count == 0) {
                    count = dataArray.size();
                }

                // align to 256
                sizeInBytes = (max(stride * count, sizeInBytes) + 0xFF) & ~0xFF;
                
                data    = (byte_t*)malloc(sizeInBytes);

                byte_t* ptr = data;
                for(size_t i = 0; i < dataArray.size(); i++) {
                    auto& object = dataArray.at(i);
                    for(auto& descriptor : descriptors) {
                        auto& element = object.property(descriptor.semanticName.c_str());
                        // how to know if the property is empty                   
                        
                        switch(descriptor.format) {
                            case eDataFormat_R32G32B32_FLOAT:
                            case eDataFormat_R32G32B32A32_FLOAT:
                                fetch<f32>(element, ptr);
                                break;
                            case eDataFormat_R8G8B8A8_UNORM:
                                fetch<u8>(element, ptr);
                                break;
                        }
                        ptr += descriptor.size;
                        element.close();
                    }
                    object.close();
                }
                dataArray.close();

                return sly::success();
            }    

            template<typename T>
            void fetch(sly::IDeserializer& array, byte_t* buffer) {
                for(size_t i = 0; i < array.size(); i++) {                    
                    array.at(i).read(*reinterpret_cast<T*>(buffer));
                    buffer += sizeof(T);
                }
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

