#pragma once

#include "sly/global.h"
#include "sly/collections/iterator.h"

namespace sly {

    template<typename TItemType, typename UnaryFunction>
    class WhereIterator : public Iterator<TItemType>
    {
        public:
            WhereIterator(const Enumerable<TItemType>* source, UnaryFunction function); // same as constructor for

            virtual TItemType current() const;
            virtual bool_t moveNext() const;

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
        
        private:
            UnaryFunction function_;
    };

    #include "sly/collections/iterators/whereiterator.hpp"

}