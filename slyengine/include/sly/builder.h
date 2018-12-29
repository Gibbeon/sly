#pragma once

#include "sly/global.h"

namespace sly {
    template<typename TDescType>
    class Builder {
    public:
        ref_t<TDescType> Build();

    protected:
        TDescType _desc;
    };

    #include "sly/builder.hpp"
}