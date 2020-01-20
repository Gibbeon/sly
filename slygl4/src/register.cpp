#include "sly/global.h"
#include "sly/platform.h"
#include "sly/gl4.h"
#include "sly/gl4/rendersystem.h"

extern "C" __declspec( dllexport ) void _CreateRenderInterface(sly::gfx::IRenderInterface** ppRenderer, sly::gfx::Renderer& desc) {
    (*ppRenderer) = new sly::gfx::GL4RenderInterface();
};
