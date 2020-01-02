#pragma once

#include "sly/global.h"


namespace sly {
    template<typename TType>
    class Builder {
    public:
        virtual ~Builder() {}
        virtual retval<TType&> build();

        virtual retval<void> init(const TType& initial) {
            desc_ = initial;
            return make_return();
        }

    protected:        
        Builder()  {}
        Builder(TType initial) : desc_(initial) {}
        Builder(TType& initial) : desc_(initial) {}
        
        TType desc_;
    };

    template <typename TType>
    retval<TType&> Builder<TType>::build() { 
        return desc_; 
    }
}