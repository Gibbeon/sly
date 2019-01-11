#include "sly/runtime/activator.h"

using namespace sly;

Activator::Activator(std::function<vptr_t(IHeap&)> ctor) : 
_ctor(ctor) {

}

template<typename TType>
Activator::Activator(std::function<TType*(IHeap&)> ctor) {
    _ctor = ([=](IHeap& heap) { return reinterpret_cast<vptr_t>(ctor(heap));});
}

template<typename TType>
TType* Activator::create(IHeap& heap) {
    return reinterpret_cast<TType*>(_ctor(heap));
}

vptr_t Activator::create(IHeap& heap) {
    return create<vptr_t>(heap);
}
