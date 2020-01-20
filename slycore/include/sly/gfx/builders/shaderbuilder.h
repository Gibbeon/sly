#pragma once

#include <string>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        struct ShaderDesc {
        public:
            vptr_t data;
            size_t size;
            std::string entry;
            std::string target;
            std::string name;
        };
        
        class ShaderBuilder : public Builder<ShaderDesc> {
        public:
            ShaderBuilder() : Builder() {}
            virtual ~ShaderBuilder() {}

            ShaderBuilder& setData(vptr_t data, size_t size) { _descriptor.data = data; _descriptor.size = size; return * this; }
            ShaderBuilder& setEntryPoint(gsl::zstring<> entry) { _descriptor.entry = entry; return * this; }
            ShaderBuilder& setTarget(gsl::zstring<> target) { _descriptor.target = target; return * this; }
            ShaderBuilder& setName(gsl::zstring<> name) { _descriptor.name = name; return * this; }
        };
    }
}
