#pragma once

#include "sly/global.h"
#include "sly/gfx/rendersystem.h"


namespace sly { 
    namespace os {
        class IOperatingSystem;
    }
    class IPluginManager;
    class IMemoryManager;

    ENUM_DECL(eSystemMemoryHeap,
        eSystemMemoryHeap_Default,
        eSystemMemoryHeap_Resources,
       eSystemMemoryHeap_Debug
    );

    ENUM_DECL(eLogLevel,
        eLogLevel_Info
    );

        struct MemoryHeapDesc {
    public:
    };

    class MemoryHeapBuilder : public Builder<MemoryHeapDesc> {
    public:
        MemoryHeapBuilder() : Builder() {}
        virtual ~MemoryHeapBuilder() {}

        MemoryHeapBuilder& setBytes(u8* buffer, size_t size) { return *this; } 
        MemoryHeapBuilder& setSize(size_t value) { return *this; } 
        MemoryHeapBuilder& setAllocHeap(eSystemMemoryHeap heap) { return *this; } 
        MemoryHeapBuilder& setDebugHeap(eSystemMemoryHeap heap) { return *this; } 
        MemoryHeapBuilder& setDebug(bool_t heap) { return *this; }            
    };
    
    struct EngineDesc {
    public:
    };

    class EngineBuilder : public Builder<EngineDesc> {
    public:
        EngineBuilder() : Builder() {}
        virtual ~EngineBuilder() {}

        EngineBuilder& setSystemMemoryHeap(eSystemMemoryHeap heap, MemoryHeapDesc& desc) { return *this; } 
        EngineBuilder& setLogLevel(eLogLevel heap) { return *this; } 
            
    };

    class Engine {
    public:
        //virtual ~Engine() {}

        static void init(EngineDesc& desc);
        static void shutdown();

        static retval<std::unique_ptr<gfx::IRenderSystem>> createRenderSystem(gfx::RenderSystemDesc& desc);

        static os::IOperatingSystem& OS() { return *(getInstance()._os); }
        static IMemoryManager& MemoryManager() { return *(getInstance()._mem); }
        static IPluginManager& Plugins() { return *(getInstance()._plugins); }
    
    private:
        os::IOperatingSystem* _os;
        IMemoryManager* _mem;
        IPluginManager* _plugins;

        static Engine& getInstance();

        Engine();
    };
}

extern sly::os::IOperatingSystem* _GetOperatingSystem();
extern sly::IPluginManager* _GetPluginManager();
extern sly::IMemoryManager* _GetMemoryManager();


