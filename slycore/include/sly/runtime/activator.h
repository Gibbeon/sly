#pragma once

#include <functional>
#include "sly/global.h"

namespace sly {
    class IActivator {
    public:
        virtual ~IActivator() {}           
        virtual vptr_t create(mem::IHeap& heap) = 0;
    
    protected:
        IActivator() {}
    };


    class DefaultActivator : public IActivator {
    public:
        DefaultActivator(std::function<vptr_t(mem::IHeap&)> ctor) : 
        _ctor(ctor) {

        }

        template<typename TType>
        DefaultActivator(std::function<TType*(mem::IHeap&)> ctor) :
            this([&](heap) { return reinterpret_cast<vptr_t>(ctor(heap));}) {
            
        }

        template<typename TType>
        TType* create(mem::IHeap& heap) {
            return reinterpret_cast<TType>(_ctor(heap));
        }

        vptr_t create(mem::IHeap& heap) {
            return create<vptr_t>(heap);
        }


    protected:
        std::function<vptr_t(mem::IHeap&)> _ctor;
    };
}
