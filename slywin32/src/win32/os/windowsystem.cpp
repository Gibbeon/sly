#include "sly/win32/os/windowsystem.h"
#include "sly/win32/os/window.h"

using namespace sly::os;

Win32WindowSystem::Win32WindowSystem(sly::Kernel& kernel) : _kernel(kernel) {

}

Win32WindowSystem::~Win32WindowSystem() {

}

sly::retval<void> Win32WindowSystem::init() {
    return success();
}

sly::retval<void> Win32WindowSystem::release() {
    return success();
}

sly::retval<std::shared_ptr<IWindow>>  Win32WindowSystem::create(const WindowDesc& desc) {
    auto window = std::make_shared<Win32Window>(*this);
    
    if(window->init(desc).failed()) {
        return failed<std::shared_ptr<IWindow>>();
    }

    return _windows.emplace_back(std::move(window));
}

sly::retval<void> Win32WindowSystem::release(IWindow& window) {
    auto result = std::remove_if(_windows.begin(), _windows.end(), [&](const std::shared_ptr<IWindow>& inner) { return inner.get() == std::addressof(window); });
    _windows.erase(result, _windows.end());
    return success();
}

gsl::span<const std::shared_ptr<IWindow>> Win32WindowSystem::windows() const {
    return gsl::span(_windows.data(), _windows.size());
}