#pragma once

#include "sly/global.h"

namespace sly {
    class IApplication;
    class IRenderSystem;
    struct ApplicationDesc;
    struct RenderSystemDesc;

    class Platform {
    public:
        static void CreateApplication(out_ptr_t<IApplication> outApplication, ref_t<ApplicationDesc> desc);
        static void CreateRenderSystem(out_ptr_t<IRenderSystem> outRenderSystem, ref_t<RenderSystemDesc> desc);
        static void SetApplication(ref_t<IApplication> application);
        static void SetRenderSystem(ref_t<IRenderSystem> application);
    };
}
