#pragma once

#include <map>

#include "sly/global.h"
#include "sly/mem/heap.h"

namespace sly {
    IHeap& getGlobalHeap();
    void setGlobalHeap(IHeap& heap);

    extern IHeap* _globalHeap;
}

