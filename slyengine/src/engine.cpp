#include "sly/engine.h"
#include "sly/os/os.h"
#include "sly/ext/pluginmanager.h"
#include "sly/mem/memorymanager.h"
#include "sly/gfx/rendersystem.h"
#include "sly/mem/globalheap.h"

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

void Engine::init(EngineDesc& desc) {
    static MallocHeap heap;
    setGlobalHeap(heap);

    getInstance()._mem = _GetMemoryManager();
    getInstance()._plugins = _GetPluginManager();
    getInstance()._os = _GetOperatingSystem();

    OS().init();

    static const size_t max = 16;
    pfRegisterPlugins ppfRegistrationFunctions[max];

    size_t count = OS().getPluginRegistrationFunctions(ppfRegistrationFunctions, max);

    for(size_t i = 0; i < count; i++ ) {
        ppfRegistrationFunctions[i](Plugins());
    }
}

retval<std::unique_ptr<gfx::IRenderSystem>> Engine::createRenderSystem(gfx::RenderSystemDesc& desc) {

    std::unique_ptr<gfx::IRenderSystem> pointer;
    pointer.reset(Plugins().get<gfx::IRenderSystem>());

    return std::move(pointer);
}
