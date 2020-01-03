#include "sly/engine.h"
#include "sly/os/operatingsystem.h"
#include "sly/ext/pluginmanager.h"
#include "sly/mem/memorymanager.h"
#include "sly/gfx/graphicsystem.h"
#include "sly/mem/globalheap.h"

using namespace sly;

retval<void> Engine::init(EngineDesc& desc) { 
    auto osResult = _os.init(os::OperatingSystemBuilder().build());
    if(osResult.failed()) {
        return failed<void>();
    }

    static MemoryManager memory;
    MemoryManagerBuilder memoryBuilder;
    auto memoryResult = (_memory = &memory)->init(memoryBuilder.build());
    
    if(memoryResult.failed()) {
        return failed<void>();
    }

    static GraphicSystem graphics;
    GraphicSystemBuilder graphicsBuilder;
    auto graphicsResult = (_graphics = &graphics)->init(graphicsBuilder.build());
    
    if(graphicsResult.failed()) {        
        return failed<void>();
    }

    static PluginManager plugins;
    PluginManagerBuilder pluginManagerBuilder;
    auto pluginResult = (_plugins = &plugins)->init(pluginManagerBuilder.build());
    
    if(pluginResult.failed()) {       
        return failed<void>();
    }

    return success();
}
