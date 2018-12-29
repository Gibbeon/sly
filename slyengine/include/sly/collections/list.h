#pragma once

#include "sly/global.h"
#include "sly/function.h"
#include "sly/collections/collection.h"
#include "sly/sys/memory.h"
#include "sly/math/math.h"


namespace sly {

    template <typename TItemType>
    class List: public Collection<TItemType>
    {
        public:
            List();
            List(s32 capacity);

            ~List();
            
            s32 add(const TItemType item);
            void addRange(const TItemType* array, s32 count);

            void insert(s32 index, const TItemType item);
            void insertRange(s32 index, const TItemType* array, s32 count);

            void remove(s32 index);
            
            TItemType get(s32 index) const;
            void set(s32 index, const TItemType item);

            void clear();
            void ensure(s32 length);

            TItemType operator[](const s32 index) const;
            TItemType& operator[](const s32 index);

            s32 count() const;
            s32 capacity() const;

            s32 indexOf(TItemType key) const;

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
            
        private:
            TItemType* items_;
            s32 count_;
            s32 capacity_;
            s32 growBy_;

            void resize(s32 capacity);
            TItemType* ptr() const;
    };

    #include "sly/collections/list.hpp"
}