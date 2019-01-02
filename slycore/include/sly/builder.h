#pragma once

#include <initializer_list>
#include "sly/global.h"


namespace sly {
    template<typename TDescType>
    class Builder {
    public:
        virtual TDescType& build();

    protected:
        Builder(TDescType initial) : desc_(initial) {}
        Builder(TDescType& initial) : desc_(initial) {}
        
        TDescType desc_;
    };

    template <typename TDescType>
    TDescType& Builder<TDescType>::build() { 
        return desc_; 
    }
}