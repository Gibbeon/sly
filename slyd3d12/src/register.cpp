#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/d3d12.h"
#include "sly/d3d12/gfx/renderer.h"
#include "sly/ext/pluginmanager.h"

extern "C" __declspec( dllexport ) sly::retval<sly::IPlugin*> _RegisterPlugins(sly::IPluginManager& manager) {
    static sly::gfx::D3D12RendererImpl instance;
    return &instance;
};
