#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/d3d12.h"
#include "sly/d3d12/gfx/rendersystem.h"
#include "sly/ext/pluginmanager.h"

extern "C" __declspec( dllexport ) void _RegisterPlugins(sly::IPluginManager& manager) {
    static sly::gfx::D3D12RenderSystemImpl instance;

    manager.set<sly::gfx::IRenderSystem>(instance);
};
