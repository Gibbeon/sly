#pragma once

#include "sly/global.h"

namespace sly {

    template <typename TItemType, typename TCollectionType = List<TItemType>>
    class Stack : public Collection<TItemType>
    {
        public:
            void push(const TItemType item);
            TItemType pop();
            TItemType peek() const;

            s32 count() const;

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;

        private:
            TCollectionType list_;
    };

    #include "sly/collections/stack.hpp"

}