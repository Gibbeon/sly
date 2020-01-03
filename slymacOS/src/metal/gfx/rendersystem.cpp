#include "sly/metal/gfx/renderer.h"
#include "sly/metal/gfx/device.h"

using namespace sly::gfx;

sly::retval<std::unique_ptr<IDevice>> METALRendererImpl::createDevice(DeviceDesc& desc)
{
    std::unique_ptr<IDevice> result = std::make_unique<METALDeviceImpl>(*this);
    result->init(desc);

    return std::move(result);
}