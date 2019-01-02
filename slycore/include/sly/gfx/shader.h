#pragma once

#include <string>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        struct ShaderDesc {
        public:
            void* data;
            size_t size;
            std::string entry;
            std::string target;
            std::string name;
        };

        class IShader : public IResource {
        public:
            virtual void init(ShaderDesc& desc) = 0;
        protected:
            using IResource::IResource;
        };
        
        class ShaderBuilder : public Builder<ShaderDesc> {
        public:
            ShaderBuilder() : Builder({}) {}
            ShaderBuilder& setData(void* data, size_t size) { desc_.data = data; desc_.size = size; return * this; }
            ShaderBuilder& setEntryPoint(std::string entry) { desc_.entry = entry; return * this; }
            ShaderBuilder& setTarget(std::string target) { desc_.target = target; return * this; }
            ShaderBuilder& setName(std::string name) { desc_.name = name; return * this; }
        };
    }
}
