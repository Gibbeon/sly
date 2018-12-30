#pragma once

#include "sly/global.h"
#include "sly/collections/array.h"
#include "sly/collections/iterator.h"
#include "sly/collections/iterators/castiterator.h"
#include "sly/collections/iterators/selectiterator.h"
#include "sly/collections/iterators/whereiterator.h"
#include "sly/collections/iterators/rangeiterator.h"

#include "sly/math/statistics/min.h"
#include "sly/math/statistics/max.h"
#include "sly/math/statistics/average.h"

#undef min
#undef max

namespace sly {
        
    template <typename TItemType>
    class Enumerable
    {
        public:
            operator Iterator<TItemType>() const;
            virtual Iterator<TItemType> getIterator() const;

            TItemType first() const;
            template <typename UnaryFunction>
            TItemType first(UnaryFunction lambda) const;

            template <typename UnaryFunction>
            WhereIterator<TItemType, UnaryFunction> where(UnaryFunction lambda) const;

            template <typename UnaryFunction>
            void foreach(UnaryFunction lambda) const;

            template<typename TConvertType>
            CastIterator<TItemType, TConvertType> cast() const;

            template<typename TConvertType, typename UnaryFunction>
            SelectIterator<TItemType, TConvertType, UnaryFunction> select(UnaryFunction lambda) const;

            size_t count() const;

            TItemType sum() const;
            
            TItemType min() const;

            TItemType max() const;

            TItemType average() const;

            bool_t any() const;

            void copy(TItemType* destination, size_t count) const;
            static void copy(const Enumerable<TItemType>& src, TItemType* destination, size_t count);

            template <typename UnaryFunction>
            bool_t any(UnaryFunction lambda) const;

            template <typename UnaryFunction>
            bool_t all(UnaryFunction lambda) const;

            RangeIterator<TItemType> skip(size_t count) const;

            RangeIterator<TItemType> take(size_t count) const;

            // sort, reverse, union?, zip?, groupBy?

        protected:
            virtual TItemType read(ptr_t state) const = 0;
            virtual bool_t next(ptr_t* state) const = 0;
        
        template<typename TSource, typename TDestination>
        friend class CastIterator;
        
        template<typename TSource, typename TDestination, typename UnaryFunction>
        friend class SelectIterator;
        
        template<typename TSource, typename UnaryFunction>
        friend class WhereIterator;

        template <typename TSource>
        friend class RangeIterator;

        template <typename TSource>
        friend class Iterator;
    };

    #include "sly/collections/enumerable.hpp"

}
