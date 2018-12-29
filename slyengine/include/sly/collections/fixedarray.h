#pragma once

#include "sly/global.h"
#include "sly/function.h"
#include "sly/collections/collection.h"
#include "sly/math/math.h"

namespace sly {
    
    template <typename TItemType, s32 Length>
    class FixedArray: public Collection<TItemType>
    {
        public:
            FixedArray(const TItemType* items);
            FixedArray(TItemType* items);

            TItemType get(s32 index) const;
            void set(s32 index, const TItemType item);

            TItemType& operator[](const s32 index);

            s32 count() const;

            s32 LENGTH = Length;

            TItemType* ptr() const;
        private:
            TItemType* items_;

        protected:
            void init(TItemType* items);

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
    };

    #include "sly/collections/fixedarray.hpp"

}