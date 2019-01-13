#include "sly/engine.h"
#include "sly/os/os.h"
#include "sly/ext/pluginmanager.h"
#include "sly/mem/memorymanager.h"
#include "sly/gfx/rendersystem.h"

using namespace sly;

IPluginManager* _GetPluginManager() {
    static PluginManager instance;
    return &instance;
}

IMemoryManager* _GetMemoryManager() {
    static MemoryManager instance;
    return &instance;
}

Engine::Engine() 
{

}

Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

void Engine::init() {

    getInstance()._mem = _GetMemoryManager();
    getInstance()._plugins = _GetPluginManager();
    getInstance()._os = _GetOperatingSystem();

    OS().init();
}

void Engine::createRenderSystem(gfx::IRenderSystem** outRenderSystem) {
    (*outRenderSystem) = Plugins().get<gfx::IRenderSystem>();
}
