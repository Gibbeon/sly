#pragma once

#include "sly/global.h"
#include "sly/os/operatingsystem.h"
#include "sly/gfx/graphicsystem.h"
#include "sly/builders/enginebuilder.h"

namespace sly { 
    class IPluginManager;
    class IMemoryManager;

    /*ENUM_DECL(eSystemMemoryHeap,
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
    };*/

    using namespace sly::os;
    using namespace sly::gfx;

    class Engine {
    public:        
        Engine():
            _os(nullptr),
            _memory(nullptr),
            _plugins(nullptr), 
            _graphics(nullptr)
        { 
        }
        
        virtual ~Engine() { shutdown(); }
        
        Engine( Engine const& )              = delete;
        Engine( Engine && )                  = delete;
        Engine& operator = ( Engine const& ) = delete;
        Engine& operator = ( Engine && )     = delete;

        retval<void> init(EngineDesc& desc);
        retval<void> shutdown() { return success(); }

        IPluginManager&         plugins() { return *_plugins; }
        IMemoryManager&         memory() { return *_memory; }
        IFileSystem&            filesystem() { return _os->filesystem(); }
        IGraphicSystem&         graphics() { return *_graphics; }

        //IInputSystem&              graphics() { return *_os; }
        //ISoundSystem&              graphics() { return *_os; }
        
        
        //retval<ILogger&>            logger() { return *_os; }
        //retval<IDebugger&>          debuger() { return *_os; }
        //retval<IProfiler&>          profiler() { return *_os; }

        //retval<std::unique_ptr<gfx::IRenderer>> Engine::createRenderer(gfx::RendererDesc& desc) { return failed<std::unique_ptr<gfx::IRenderer>>(); }

    protected:
        //static retval<void> set(Engine* instance) { _instance = instance; return success(); }
    
    private: 

        //Engine(Engine* instance) { set(instance); }

        gsl::owner<IOperatingSystem*>   _os;
        gsl::owner<IMemoryManager*>     _memory;
        gsl::owner<IPluginManager*>     _plugins;
        gsl::owner<IGraphicSystem*>     _graphics;

        //static gsl::owner<Engine*>      _instance;
    };
}

extern sly::os::IOperatingSystem* _GetOperatingSystem();


