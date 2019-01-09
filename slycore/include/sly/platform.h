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

    namespace os {
        class IOperatingSystem;
    }
    
    class Platform {
    public:
        static void initialize();
        static void shutdown();

        static void createApplication(IApplication** outApplication, ApplicationDesc& desc);
        static void createRenderSystem(gfx::IRenderSystem** outRenderSystem, gfx::RenderSystemDesc& desc);
        
        static void registerRenderSystem(std::string name, std::function<void(gfx::IRenderSystem**, gfx::RenderSystemDesc&)> fn);

        static sly::os::IOperatingSystem& OS() { return *_os; }
    
    private:
        static sly::os::IOperatingSystem* _os;
        static std::map<std::string, std::function<void(gfx::IRenderSystem**, gfx::RenderSystemDesc&)>> _renderSystems;
    };
}

extern void _CreateOperatingSystemImpl(sly::os::IOperatingSystem** os);
