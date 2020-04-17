#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/renderstatebuilder.h"

namespace sly {
    namespace gfx {
        struct RootSignatureDesc;
        class IRootSignature {
        public:
            virtual ~IRootSignature() {}
            
            virtual retval<void> init(const RootSignatureDesc& desc) = 0;

        protected:
            IRootSignature() {}

        };
    }
}
