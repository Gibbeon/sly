#include "sly/d3d12/gfx/rendersystem.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/win32.h"

using namespace sly::gfx;

sly::retval<std::unique_ptr<IDevice>> D3D12RenderSystemImpl::createDevice(DeviceDesc& desc)
{
    std::unique_ptr<IDevice> result = std::make_unique<IDevice>( new D3D12DeviceImpl(*this) );
    result->init(desc);

    return return_value(result);
}