#include "sly/metal/gfx/rendersystem.h"
#include "sly/metal/gfx/device.h"

using namespace sly::gfx;

void METALRenderSystemImpl::createDevice(IDevice** result, DeviceDesc& desc)
{
    (*result) = new METALDeviceImpl(*this);
    (*result)->init(desc);
}