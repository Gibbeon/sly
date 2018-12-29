#pragma once

#include "sly/global.h"
#include "sly/collections/iterator.h"

namespace sly {

    template<typename TSource, typename TDestination>
    class CastIterator : public Iterator<TDestination>
    {
        public:
            CastIterator(const Enumerable<TSource>* source); // same as constructor for

            virtual TDestination current() const;
            virtual bool_t moveNext() const;

        protected:
            virtual TDestination read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
        
        private:
            const Enumerable<TSource>* castSource_;
            mutable ptr_t cursor_;
    };

    #include "sly/collections/iterators/castiterator.hpp"
}