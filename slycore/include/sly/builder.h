#pragma once

#include "sly/global.h"


namespace sly {
    template<typename TDescType>
    class Builder {
    public:
        virtual ~Builder() {}
        virtual TDescType& build();

    protected:        
        Builder()  {}
        Builder(TDescType initial) : desc_(initial) {}
        Builder(TDescType& initial) : desc_(initial) {}
        
        TDescType desc_;
    };

    template <typename TDescType>
    TDescType& Builder<TDescType>::build() { 
        return desc_; 
    }
}