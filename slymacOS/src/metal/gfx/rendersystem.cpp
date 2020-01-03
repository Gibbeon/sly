#include "sly/metal/gfx/rendersystem.h"
#include "sly/metal/gfx/device.h"

using namespace sly::gfx;

retval<std::unique_ptr<IDevice>> METALRendererImpl::createDevice(DeviceDesc& desc)
{
    (*result) = new METALDeviceImpl(*this);
    (*result)->init(desc);
}