#include "sly/win32/os/os.h"
#include "sly/gfx/rendersystem.h"
#include "sly/platform.h"

using namespace sly::os;

typedef void (APIENTRY * pfCreateRenderSystem) (sly::gfx::IRenderSystem** ppRenderSystem, sly::gfx::RenderSystem& desc);

Win32OperatingSystem::Win32OperatingSystem() {
    HMODULE h = LoadLibraryA("c:/dev/sly/slyd3d12/bin/slyd3d12.dll");
    
    pfCreateRenderSystem pf = (pfCreateRenderSystem)GetProcAddress(h, "_CreateRenderSystemImpl");
    
    sly::Platform::registerRenderSystem("D3D12", pf);

}