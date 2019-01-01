#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        struct ShaderDesc {
        public:
            ptr_t data;
            size_t size;
            string_t entry;
            string_t target;
            string_t name;
        };

        class IShader : public IResource {
        public:
            virtual void init(ref_t<ShaderDesc> desc = IShader::DEFAULT_DESC) = 0;
        protected:
            using IResource::IResource;
            
            constexpr static ShaderDesc DEFAULT_DESC = { 0, 0, "", "" }; 
            friend class ShaderBuilder;
        };
        
        class ShaderBuilder : public Builder<ShaderDesc> {
        public:
            ShaderBuilder() : Builder(IShader::DEFAULT_DESC) {}
            ShaderBuilder& setData(ptr_t data, size_t size) { desc_.data = data; desc_.size = size; return * this; }
            ShaderBuilder& setEntryPoint(string_t entry) { desc_.entry = entry; return * this; }
            ShaderBuilder& setTarget(string_t target) { desc_.target = target; return * this; }
            ShaderBuilder& setName(string_t name) { desc_.name = name; return * this; }
        };
    }
}
