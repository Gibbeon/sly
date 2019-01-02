#pragma once

#include <functional>

#include "sly/platform.h"
#include "sly/application.h"
#include "sly/gfx/rendersystem.h"

using namespace sly;

sly::sys::IOperatingSystem* Platform::_os = NULL;
std::map<std::string, std::function<void(gfx::IRenderSystem**, gfx::RenderSystemDesc&)>> Platform::_renderSystems;

void Platform::initialize() {
    _CreateOperatingSystemImpl(&_os);
}

void Platform::createApplication(IApplication** outApplication, ApplicationDesc& desc) {
    (*outApplication) = new SlyApplication();
}

void Platform::createRenderSystem(gfx::IRenderSystem** outRenderSystem, gfx::RenderSystemDesc& desc) {
    _renderSystems["D3D12"](outRenderSystem, desc);
}

void Platform::registerRenderSystem(std::string name, std::function<void(gfx::IRenderSystem**, gfx::RenderSystemDesc&)> fn)
{
    _renderSystems.insert_or_assign(name, fn);
    auto value = _renderSystems["D3D12"];    
    _renderSystems[name] = value;
}
