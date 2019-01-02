#pragma once

#include "sly/global.h"

#include <string>
#include <functional>
#include <map>

namespace sly {
    class IApplication;
    struct ApplicationDesc;
    
    namespace gfx {
        class IRenderSystem;
        struct RenderSystemDesc;
    }

    namespace sys {
        class IOperatingSystem;
    }
    
    class Platform {
    public:
        static void initialize();
        static void shutdown();

        static void createApplication(IApplication** outApplication, ApplicationDesc& desc);
        static void createRenderSystem(gfx::IRenderSystem** outRenderSystem, gfx::RenderSystemDesc& desc);
        
        static void registerRenderSystem(std::string name, std::function<void(gfx::IRenderSystem**, gfx::RenderSystemDesc&)> fn);
    
    private:
        static sly::sys::IOperatingSystem* _os;
        static std::map<std::string, std::function<void(gfx::IRenderSystem**, gfx::RenderSystemDesc&)>> _renderSystems;
    };
}

extern void _CreateOperatingSystemImpl(sly::sys::IOperatingSystem** os);
