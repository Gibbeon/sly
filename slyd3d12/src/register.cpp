#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/d3d12.h"
#include "sly/d3d12/gfx/rendersystem.h"
#include "sly/ext/pluginmanager.h"

extern __declspec( dllexport ) sly::retval<sly::IPlugin*> _RegisterPlugins(sly::IPluginManager& manager) {
    static sly::gfx::D3D12RendererImpl instance;
    return &instance;
};
