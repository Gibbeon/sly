#pragma once

#include "sly/global.h"
#include "sly/collections/iterator.h"

namespace sly {

    template<typename TItemType>
    class RangeIterator : public Iterator<TItemType>
    {
        public:
            RangeIterator(const Enumerable<TItemType>* source, s32 skip = 0, s32 take = -1); // same as constructor for

            virtual TItemType current() const;
            virtual bool_t moveNext() const;

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
        
        private:
            s32 skip_;
            u32 take_;
            s32 index_;
    };

    #include "sly/collections/iterators/rangeiterator.hpp"

}