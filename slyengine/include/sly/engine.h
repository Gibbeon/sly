#pragma once

#include "sly/global.h"
#include "sly/gfx/rendersystem.h"


namespace sly { 

    class IOperatingSystem;
    class IPluginManager;
    class IMemoryManager;

    class Engine {
    public:
        //virtual ~Engine() {}

        static void init();
        static void shutdown();

        static void createRenderSystem(gfx::IRenderSystem** outRenderSystem);

        static IOperatingSystem& OS() { return *(getInstance()._os); }
        static IMemoryManager& MemoryManager() { return *(getInstance()._mem); }
        static IPluginManager& Plugins() { return *(getInstance()._plugins); }
    
    private:
        IOperatingSystem* _os;
        IMemoryManager* _mem;
        IPluginManager* _plugins;

        static Engine& getInstance();

        Engine();
    };
}

extern sly::IOperatingSystem* _GetOperatingSystem();
extern sly::IPluginManager* _GetPluginManager();
extern sly::IMemoryManager* _GetMemoryManager();


