#pragma once

#include "sly/global.h"

namespace sly {
    class IAllocator {
    public:
        virtual ~IAllocator() {}

        virtual vptr_t alloc(u32 size) = 0;
        virtual void free(vptr_t ptr) = 0;

        virtual void reset();

    protected:
        IAllocator() {}
    };
}