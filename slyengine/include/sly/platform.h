#pragma once

#include "sly/global.h"
#include "sly/collections/map.h"

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

        static void createApplication(out_ptr_t<IApplication> outApplication, ref_t<ApplicationDesc> desc);
        static void createRenderSystem(out_ptr_t<gfx::IRenderSystem> outRenderSystem, ref_t<gfx::RenderSystemDesc> desc);
        
        static void registerRenderSystem(String<> name, Function<void(out_ptr_t<gfx::IRenderSystem>, ref_t<gfx::RenderSystemDesc>)> fn);
    
    private:
        static ref_t<sly::sys::IOperatingSystem> os_;
        static Map<String<>, Function<void(out_ptr_t<gfx::IRenderSystem>, ref_t<gfx::RenderSystemDesc>)>> renderSystems_;
    };
}

extern void _CreateOperatingSystemImpl(out_ptr_t<sly::sys::IOperatingSystem> os);
