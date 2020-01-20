#pragma once 

#include "sly/global.h"
//#include "sly/win32/global.h"

#include <initguid.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>

#include "sly/gfx/renderinterface.h"

namespace sly { namespace d3d12 { namespace gfx { 
    extern "C" sly::gfx::IRenderInterface* GetRenderInterface(sly::Kernel& kernel = sly::Kernel::get());
}}}


