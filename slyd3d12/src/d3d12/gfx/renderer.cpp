#include "sly/d3d12/gfx/renderer.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/win32.h"

using namespace sly::gfx;

sly::retval<std::unique_ptr<IDevice>> D3D12RendererImpl::createDevice(DeviceDesc& desc)
{
    std::unique_ptr<IDevice> result = std::make_unique<D3D12DeviceImpl>(*this);
    result->init(desc);

    return std::move(result);

}