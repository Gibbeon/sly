#pragma once

#include "sly/global.h"


namespace sly {
    template<typename TType>
    class Builder {
    public:
        virtual ~Builder() {}
        virtual const TType& build();

        virtual void init(const TType& initial) {
            _descriptor = initial;
        }

    protected:        
        Builder() {}
        Builder(TType initial) : _descriptor(initial) {}
        Builder(TType& initial) : _descriptor(initial) {}
        
        TType _descriptor;
    };

    template <typename TType>
    const TType& Builder<TType>::build() { 
        return reference(_descriptor); 
    }
}