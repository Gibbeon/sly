#include "sly/global.h"
#include "sly/platform.h"
#include "sly/gl4.h"
#include "sly/gl4/rendersystem.h"

extern "C" __declspec( dllexport ) void _CreateRenderSystemImpl(sly::gfx::IRenderSystem** ppRenderSystem, sly::gfx::RenderSystem& desc) {
    (*ppRenderSystem) = new sly::gfx::GL4RenderSystemImpl();
};
