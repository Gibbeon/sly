#pragma once

#include <functional>
#include "sly/global.h"

namespace sly {
    class IHeap;
    class IActivator {
    public:
        virtual ~IActivator() {}           
        virtual vptr_t create(IHeap& heap) = 0;
    
    protected:
        IActivator() {}
    };

    class Activator : public IActivator {
    public:
        Activator(std::function<vptr_t(IHeap&)> ctor);

        template<typename TType>
        Activator(std::function<TType*(IHeap&)> ctor);

        template<typename TType>
        TType* create(IHeap& heap);

        vptr_t create(IHeap& heap);
    protected:
        std::function<vptr_t(IHeap&)> _ctor;
    };
}
