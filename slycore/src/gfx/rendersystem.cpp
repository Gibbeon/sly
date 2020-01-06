#include "sly/gfx/rendersystem.h"

using namespace sly::gfx;

RenderSystem::RenderSystem(sly::Kernel& kernel) : _kernel(kernel) {

}

RenderSystem::~RenderSystem() {

}

sly::retval<void> RenderSystem::init() {
    return success();

}

sly::retval<void> RenderSystem::release() {
    return success();
}

std::vector<IRenderInterface*>& RenderSystem::interfaces() {
    return _interfaces;
}