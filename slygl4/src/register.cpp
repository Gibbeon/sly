#include "sly/global.h"
#include "sly/platform.h"
#include "sly/gl4.h"
#include "sly/gl4/rendersystem.h"

extern "C" __declspec( dllexport ) void _CreateRendererImpl(sly::gfx::IRenderer** ppRenderer, sly::gfx::Renderer& desc) {
    (*ppRenderer) = new sly::gfx::GL4RendererImpl();
};
