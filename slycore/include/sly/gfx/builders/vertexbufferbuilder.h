#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"
#include "sly/gfx/inputelement.h"
#include "sly/gfx/builders/resourcebuilder.h"

namespace sly {
    namespace gfx {
        struct VertexBufferDesc : public ResourceDesc {
        public:
            size_t count;
        };


        class VertexBufferBuilder : public Builder<VertexBufferDesc> {
        public:
            VertexBufferBuilder() : Builder() {
                _descriptor.count = 0;
            }            
            virtual ~VertexBufferBuilder() {}

            VertexBufferBuilder& setData(vptr_t data, size_t count, size_t stride) { 
                _descriptor.data = data; 
                _descriptor.count = count; 
                _descriptor.stride = stride;  
                _descriptor.sizeInBytes = count * stride; 
                return * this; 
            }
        };
    }
}

