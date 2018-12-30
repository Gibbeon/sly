#include "sly/win32/sys/os.h"
#include "sly/gfx/rendersystem.h"
#include "sly/platform.h"

using namespace sly::sys;

typedef void (APIENTRY * pfCreateRenderSystem) (out_ptr_t<sly::gfx::IRenderSystem> ppRenderSystem, ref_t<sly::gfx::RenderSystemDesc> desc);

Win32OperatingSystem::Win32OperatingSystem() {
    HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    SLYASSERT_NOTNULL(h, "OMH");
    
    pfCreateRenderSystem pf = (pfCreateRenderSystem)GetProcAddress(h, "_CreateRenderSystemImpl");
    
    sly::Platform::registerRenderSystem("D3D12", pf);

}