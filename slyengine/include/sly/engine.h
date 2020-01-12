#pragma once

#include "sly/global.h"
#include "sly/kernel.h"
#include "sly/builders/enginebuilder.h"
#include "sly/resources/resourcesystem.h"

namespace sly { 
    class Engine {
    public:        
        Engine(Kernel& kernel = sly::Kernel::get());
        virtual ~Engine();
        
        Engine( Engine const& )              = delete;
        Engine( Engine && )                  = delete;
        Engine& operator = ( Engine const& ) = delete;
        Engine& operator = ( Engine && )     = delete;

        virtual retval<void> init(const EngineDesc& desc = EngineBuilder().build());
        virtual retval<void> release();

        virtual Kernel& kernel() const;
        virtual ResourceSystem& resources() const;

    protected:
    
    private:
        Kernel&     _kernel;
        
    };
}



