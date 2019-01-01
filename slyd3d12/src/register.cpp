#include "sly/global.h"
#include "sly/platform.h"
#include "sly/gfx.h"
#include "sly/d3d12.h"
#include "sly/d3d12/gfx/rendersystem.h"

extern "C" __declspec( dllexport ) void _CreateRenderSystemImpl(out_ptr_t<sly::gfx::IRenderSystem> ppRenderSystem, ref_t<sly::gfx::RenderSystemDesc> desc) {
    ppRenderSystem = new sly::gfx::D3D12RenderSystemImpl();
};
