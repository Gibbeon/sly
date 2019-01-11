#include <functional>

#include "sly/platform.h"
#include "sly/application.h"
#include "sly/mem/memorymanager.h"
#include "sly/gfx/rendersystem.h"

using namespace sly;

sly::IMemoryManager* Platform::_mem = NULL;
sly::os::IOperatingSystem* Platform::_os = NULL;
std::map<std::string, fpCreateRenderSystem> Platform::_renderSystems;

void Platform::initialize() {
    _CreateOperatingSystemImpl(&_os);
    _mem = new MemoryManager();
}

void Platform::createApplication(IApplication** outApplication, Application& desc) {
    (*outApplication) = new SlyApplication();
}

void Platform::createRenderSystem(gfx::IRenderSystem** outRenderSystem, gfx::RenderSystemDesc& desc) {
    _renderSystems["D3D12"](outRenderSystem, desc);
}

void Platform::registerRenderSystem(std::string name, fpCreateRenderSystem fn)
{
    _renderSystems.insert_or_assign(name, fn);
    auto value = _renderSystems["D3D12"];    
    _renderSystems[name] = value;
}
