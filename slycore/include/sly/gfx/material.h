#pragma once

#include "sly/global.h"
#include "sly/gfx.h"

namespace sly { 
    namespace gfx {
        class Material {
        protected:        
            std::vector<gfx::IShader*>      _shaders;  
            std::vector<gfx::ITexture*>     _textures;
            gfx::IRenderState*              _state; 
        };
    }
}



