#pragma once

#include "sly/global.h"
#include "sly/collections/enumerable.h"

namespace sly {

    template <typename TItemType>
    class Collection : public Enumerable<TItemType>
    {
        public:
        
    };

    #include "sly/collections/collection.hpp"

}
