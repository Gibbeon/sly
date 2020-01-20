#include "sly/global.h"
#include "sly/d3d12.h"
#include "sly/d3d12/gfx/renderinterface.h"

using namespace sly::d3d12::gfx;

extern "C" sly::gfx::IRenderInterface* sly::d3d12::gfx::GetRenderInterface(sly::Kernel& kernel) {
    static sly::gfx::D3D12RenderInterface instance(kernel);
    static bool_t initialized = false;
    
    if(!initialized) {
        instance.init();
        initialized = true;
    }

    return &instance;
}