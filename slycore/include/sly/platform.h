#pragma once

#include <string>
#include <functional>
#include <map>

#include "sly/global.h"
#include "sly/mem/memorymanager.h"
#include "sly/gfx/rendersystem.h"

typedef std::function<void(sly::gfx::IRenderSystem**, sly::gfx::RenderSystemDesc&)> fpCreateRenderSystem;

namespace sly {
    class IApplication;
    struct Application;
    
    namespace gfx {
        class IRenderSystem;
        struct RenderSystem;
    }

    namespace os {
        class IOperatingSystem;
    }
    
    class Platform {
    public:
        static void initialize();
        static void shutdown();

        static void createApplication(IApplication** outApplication, Application& desc);
        static void createRenderSystem(gfx::IRenderSystem** outRenderSystem, gfx::RenderSystemDesc& desc);
        
        static void registerRenderSystem(std::string name, fpCreateRenderSystem fn);

        static sly::os::IOperatingSystem& OS() { return *_os; }
        static sly::IMemoryManager& MemoryManager() { return *_mem; }
    
    private:
        static sly::os::IOperatingSystem* _os;
        static sly::IMemoryManager* _mem;
        static std::map<std::string, fpCreateRenderSystem> _renderSystems;
    };
}

extern void _CreateOperatingSystemImpl(sly::os::IOperatingSystem** os);
