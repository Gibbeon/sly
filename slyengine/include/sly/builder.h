#pragma once

#include "sly/global.h"

namespace sly {
    template<typename TDescType>
    class Builder {
    public:
        virtual ref_t<TDescType> build();

    protected:
        Builder(TDescType initial) : desc_(initial) {}
        TDescType desc_;
    };

    template <typename TDescType>
    ref_t<TDescType> Builder<TDescType>::build() { 
        return ref_t<TDescType>(&desc_); 
    }
}