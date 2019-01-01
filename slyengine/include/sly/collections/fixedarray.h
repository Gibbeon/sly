#pragma once

#include "sly/global.h"
#include "sly/function.h"
#include "sly/collections/collection.h"
#include "sly/math/math.h"

namespace sly {
    
    template <typename TItemType, size_t Length>
    class FixedArray: public Array<TItemType>
    {
        public:
            FixedArray() : Array(reinterpret_cast<TItemType*>(items_), Length) {}
        private:
            TItemType* items_[Length];

/*            TItemType get(size_t index) const;
            void set(size_t index, const TItemType item);

            TItemType& operator[](const size_t index);

            size_t count() const;

            size_t LENGTH = Length;

            TItemType* ptr() const;
        private:
            TItemType* items_;

        protected:
            void init(TItemType* items);

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const; */
    };

    #include "sly/collections/fixedarray.hpp"

}