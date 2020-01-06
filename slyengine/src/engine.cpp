#include "sly/engine.h"
#include "sly/kernel.h"

using namespace sly;

Engine::Engine(Kernel& kernel) :
    _kernel(kernel) {

}

Engine::~Engine() {

}

retval<void> Engine::init(const EngineDesc& desc) { 
    return success();
}

retval<void> Engine::release() {
    return success();
}

Kernel& Engine::kernel() const {
    return _kernel;
}
