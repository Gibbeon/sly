#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"
#include "sly/gfx/texture.h"

namespace sly {
    namespace gfx {
        class D3D12TextureImpl : public D3D12ResourceImpl, public ITexture {
        public:
        
        protected:
            using D3D12ResourceImpl::D3D12ResourceImpl;
        };
    }
}

