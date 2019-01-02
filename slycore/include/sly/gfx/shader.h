#pragma once

#include <string>

#include "sly/global.h"
#include "sly/gfx/managedresource.h"
#include "sly/gfx/builders/shaderbuilder.h"

namespace sly {
    namespace gfx {

        class IShader : public IManagedResource {
        public:
            virtual ~IShader() {}
            virtual void init(ShaderDesc& desc) = 0;

        protected:
            IShader() {}

        };
    }
}
