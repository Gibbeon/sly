#pragma once

#include "sly/global.h"
#include "sly/collections/enumerable.h"


namespace sly {

    template <typename TItemType>
    class Enumerable;

    template <typename TItemType>
    class Iterator : public Enumerable<TItemType>
    {
        public:
            Iterator(const Enumerable<TItemType>* source);
            
            virtual TItemType current() const;
            virtual bool_t moveNext() const;

            TItemType operator*() const;
            bool_t operator++() const;

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;

        protected:
            const Enumerable<TItemType>* source_;
            mutable ptr_t cursor_;

            Iterator() : cursor_(NULL) {}
    };

    #include "sly/collections/iterator.hpp"

}