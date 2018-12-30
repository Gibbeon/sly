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
            List(size_t capacity);

            ~List();
            
            size_t add(const TItemType item);
            void addRange(const TItemType* array, size_t count);

            void insert(size_t index, const TItemType item);
            void insertRange(size_t index, const TItemType* array, size_t count);

            void remove(size_t index);
            
            TItemType get(size_t index) const;
            void set(size_t index, const TItemType item);

            void clear();
            void ensure(size_t length);

            TItemType operator[](const size_t index) const;
            TItemType& operator[](const size_t index);

            size_t count() const;
            size_t capacity() const;

            size_t indexOf(TItemType key) const;

        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
            
        private:
            TItemType* items_;
            size_t count_;
            size_t capacity_;
            size_t growBy_;

            void resize(size_t capacity);
            TItemType* ptr() const;
    };

    #include "sly/collections/list.hpp"
}