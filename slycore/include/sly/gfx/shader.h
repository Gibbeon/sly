#pragma once

#include <string>

#include "sly/global.h"
#include "sly/gfx/managedresource.h"
#include "sly/gfx/builders/shaderbuilder.h"

namespace sly {
    namespace gfx {
        class IManagedResource;
        class IShader : public IManagedResource {
        public:
            virtual ~IShader() {}
            
            virtual retval<void> init(const ShaderDesc& desc = ShaderBuilder().build()) = 0;

        protected:
            IShader() {}

        };
    }
}
