#include "sly/mem/globalheap.h"


sly::IHeap* sly::_globalHeap = nullptr;

sly::IHeap&  sly::getGlobalHeap() {
    return *_globalHeap;
}

void sly::setGlobalHeap(sly::IHeap& heap) {
    _globalHeap = &heap;
} 