#pragma once

#include "sly/global.h"
#include "sly/function.h"
#include "sly/collections/collection.h"
#include "sly/math/math.h"

namespace sly {
    
    template <typename TItemType>
    class Array: public Collection<TItemType>
    {
        public:
            
            Array(TItemType* items, size_t count);
            Array(const TItemType* items, size_t count);
            
            Array(const Array<TItemType>& copy);
            Array(const Array<TItemType>&& copy);

            TItemType get(size_t index) const;
            void set(size_t index, const TItemType item);

            TItemType& operator[](const size_t index);

            size_t count() const;

            TItemType* ptr() const;
        private:
            TItemType* items_;
            size_t count_;

        protected:
            void init(TItemType* items, size_t count);

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
    };

    #include "sly/collections/array.hpp"

}
