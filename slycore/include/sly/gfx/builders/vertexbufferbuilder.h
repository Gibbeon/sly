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

        struct BufferDesc : public ResourceDesc {
        public:
            eBufferType type;

            

        };

        class BufferBuilder : public Builder<BufferDesc> {
        public:
            BufferBuilder() : Builder() {}        
            virtual ~BufferBuilder() {}

             BufferBuilder& setType(eBufferType type) { 
                _descriptor.type = type;
                return *this; 
            }

            BufferBuilder& setData(vptr_t data, size_t sizeInBytes, size_t stride) { 
                _descriptor.data.reset((uint_t*)data); 
                _descriptor.stride = stride;  
                _descriptor.sizeInBytes = sizeInBytes; 
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

