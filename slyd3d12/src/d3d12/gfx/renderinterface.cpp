#include "sly/win32.h"

#include "sly/d3d12/gfx/renderinterface.h"
#include "sly/d3d12/gfx/device.h"

#include "sly/mem/memorysystem.h"

using namespace sly::gfx;


D3D12RenderInterface::D3D12RenderInterface(sly::Kernel& kernel) : _kernel(kernel) {

}

D3D12RenderInterface::~D3D12RenderInterface() {

}

sly::retval<void> D3D12RenderInterface::init() {
    return success();
}

sly::retval<void> D3D12RenderInterface::release() {
    return success();
}

sly::retval<std::unique_ptr<IDevice>> D3D12RenderInterface::createDevice(const DeviceDesc& desc)
{
    std::unique_ptr<IDevice> result = std::make_unique<D3D12DeviceImpl>(*this);
    result->init(desc);

    return std::move(result);
}
