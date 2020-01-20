#include "sly/kernel.h"


#include "sly/mem/memorysystem.h"
#include "sly/os/operatingsystem.h"
#include "sly/os/windowsystem.h"
#include "sly/gfx/rendersystem.h"
#include "sly/os/windowsystem.h"


using namespace sly;

Kernel& Kernel::get() {
    static sly::Kernel instance;
    static bool initialized = false;
    
    if(!initialized) {
        instance.init();
        initialized = true;
    }

    return instance;
}

Kernel::Kernel() : 
    _initialized(FALSE) {

}

Kernel::~Kernel() {
    release();
}

retval<void> Kernel::init() {
    Expects(!_initialized);
    
    static MemorySystem         memory(*this);
    if(memory.init().failed()) {
        throw;
    } 

    _memory = &memory;

    static os::OperatingSystem  system(*this);
    if(system.init().failed()) {
        throw;
    } 
    
    _system = &system;

    static gfx::RenderSystem    gfx(*this);
    if(gfx.init().failed()) {
        throw;
    } 
    
    _gfx = &gfx;    

    _initialized = true;
    return success();
}

retval<void> Kernel::release() {
    if(_initialized) {        
        _initialized = false;
    }

    return success();
}

os::IFileSystem& Kernel::filesystem() const {
    Expects(_initialized);
    return system().filesystem();
}

os::IOperatingSystem& Kernel::system() const {
    Expects(_initialized);
    return *_system;
}

IMemorySystem& Kernel::memory() const {
    Expects(_initialized);
    return *_memory;
}

os::IWindowSystem& Kernel::windows() const {
    Expects(_initialized);
    return system().windows();
}

gfx::IRenderSystem& Kernel::graphics() const {
    Expects(_initialized);
    return *_gfx;
}

