#include "sly/d3d12/gfx/rendersystem.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/win32.h"

using namespace sly::gfx;

void D3D12RenderSystemImpl::createDevice(IDevice** result, DeviceDesc& desc)
{
    (*result) = new D3D12DeviceImpl(desc);
}