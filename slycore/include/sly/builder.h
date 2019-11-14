#pragma once

#include "sly/global.h"


namespace sly {
    template<typename TType>
    class Builder {
    public:
        virtual ~Builder() {}
        virtual TType& build();

        virtual void init(const TType& initial) {
            desc_ = initial;
        }

    protected:        
        Builder()  {}
        Builder(TType initial) : desc_(initial) {}
        Builder(TType& initial) : desc_(initial) {}
        
        TType desc_;
    };

    template <typename TType>
    TType& Builder<TType>::build() { 
        return desc_; 
    }
}