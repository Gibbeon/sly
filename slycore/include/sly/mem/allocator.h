#pragma once

#include "sly/global.h"

namespace sly {
    class IAllocator {
    public:
        virtual ~IAllocator() {}

        virtual vptr_t alloc(size_t size) = 0;
        virtual void free(vptr_t ptr) = 0;

        virtual void reset();

    protected:
        IAllocator() {}
    };
}