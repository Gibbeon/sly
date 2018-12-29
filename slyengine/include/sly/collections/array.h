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
            Array(TItemType* items, s32 count);
            Array(const TItemType* items, s32 count);
            
            Array(const Array<TItemType>& copy);
            Array(const Array<TItemType>&& copy);

            TItemType get(s32 index) const;
            void set(s32 index, const TItemType item);

            TItemType& operator[](const s32 index);

            s32 count() const;

            TItemType* ptr() const;
        private:
            TItemType* items_;
            s32 count_;

        protected:
            void init(TItemType* items, s32 count);

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
    };

    #include "sly/collections/array.hpp"

}
