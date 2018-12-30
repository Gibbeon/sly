#pragma once

#include "sly/platform.h"
#include "sly/application.h"
#include "sly/gfx/rendersystem.h"

#include "sly/function.h"

using namespace sly;

ref_t<sly::sys::IOperatingSystem> Platform::os_;
Map<String<>, Function<void(out_ptr_t<gfx::IRenderSystem>, ref_t<gfx::RenderSystemDesc>)>> Platform::renderSystems_;

void Platform::initialize() {
    _CreateOperatingSystemImpl(os_);
}

void Platform::createApplication(out_ptr_t<IApplication> outApplication, ref_t<ApplicationDesc> desc) {
    outApplication = new SlyApplication();
}

void Platform::createRenderSystem(out_ptr_t<gfx::IRenderSystem> outRenderSystem, ref_t<gfx::RenderSystemDesc> desc) {
    renderSystems_["D3D12"](outRenderSystem, desc);
}

void Platform::registerRenderSystem(String<> name, Function<void(out_ptr_t<gfx::IRenderSystem>, ref_t<gfx::RenderSystemDesc>)> fn)
{
    renderSystems_.add(name, fn);
    auto value = renderSystems_["D3D12"];    
    renderSystems_[name] = value;
}
