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
            void fillRange(const TItemType element, size_t count);

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
template <typename TItemType>
List<TItemType>::List() : 
    List(25)
{

}

template <typename TItemType>
List<TItemType>::List(size_t capacity) :
    growBy_(25),
    count_(0),
    capacity_(0),
    items_(NULL)
{
    ensure(capacity);
}

template <typename TItemType>
List<TItemType>::~List() 
{
    if(items_ != NULL)
    {
        Memory::free(items_);
        items_ = NULL;
    }
}

template <typename TItemType>
size_t List<TItemType>::add(const TItemType item)
{
    addRange(&item, 1);
    return count_;
}

template <typename TItemType>
void List<TItemType>::fillRange(const TItemType element, size_t count)
{
    ensure(count_ + count);
    
    Memory::fill(element, &items_[count_], sizeof(TItemType) * count);
    count_ += count;
}

template <typename TItemType>
void List<TItemType>::addRange(const TItemType* array, size_t count)
{
    NOT_NULL(array);

    ensure(count_ + count);
    // Function will break here, since the buf_ reference copied will be invalid... 
    // Honestly is "thi"
    Memory::copy(array, &items_[count_], sizeof(TItemType) * count);
    count_ += count;
}

template <typename TItemType>
void List<TItemType>::insert(size_t index, const TItemType item)
{
    insertRange(index, &item, 1);
}

template <typename TItemType>
void List<TItemType>::insertRange(size_t index, const TItemType* array, size_t count)
{
    BOUNDS_CHECK(count_ + 1, index);

    ensure(count_ + count);
    if(index < count_) // ignore if tail
    {
        Memory::copy(&items_[index], &items_[index + count], sizeof(TItemType) * (count_ - index));
    }

    Memory::copy(array, &items_[index], sizeof(TItemType) * (count));
    count_ += count;
}

template <typename TItemType>
void List<TItemType>::remove(size_t index)
{
    BOUNDS_CHECK(count_, index);

    if(index < count_) // ignore if tail
    {
        Memory::copy(&items_[index + 1], &items_[index], sizeof(TItemType) * (count_ - index));
    }
    --count_;
}

template <typename TItemType>
void List<TItemType>::set(size_t index, const TItemType item)
{
    BOUNDS_CHECK(count_, index);

    items_[index] = item;
}

template <typename TItemType>
TItemType List<TItemType>::get(size_t index) const
{
    BOUNDS_CHECK(count_, index);

    return items_[index];
}

template <typename TItemType>
void List<TItemType>::clear()
{
    count_ = 0;
}

template <typename TItemType>
void List<TItemType>::ensure(size_t length)
{
    SLYASSERT_GT(growBy_, 0, "GrowBy cannot be 0");
    if(length > capacity_)
    {
        resize((((length + growBy_) - 1) / growBy_) * growBy_);
    }
}

template <typename TItemType>       
size_t List<TItemType>::count() const
{
    return count_;
}

template <typename TItemType>
size_t List<TItemType>::capacity() const
{
    return capacity_;
}

template <typename TItemType>
void List<TItemType>::resize(size_t capacity)
{
    TItemType* newArray = reinterpret_cast<TItemType*>(Memory::allocate(sizeof(TItemType) * capacity));
    
    if(capacity_ > 0)
    {
        #ifdef min
        #undef min
        #endif 
        sly::Memory::copy(items_, newArray, Math::min(capacity_, capacity));
        sly::Memory::free(items_);
    }
    items_ = newArray;
    capacity_ = capacity;
}

template <typename TItemType>
TItemType& List<TItemType>::operator[](size_t index)
{
    BOUNDS_CHECK(count_, index);
    return items_[index];
}

template <typename TItemType>
TItemType List<TItemType>::operator[](size_t index) const
{
    BOUNDS_CHECK(count_, index);
    return get(index);
}

template <typename TItemType>
TItemType* List<TItemType>::ptr() const
{
    return items_;
}

template <typename TItemType>
size_t List<TItemType>::indexOf(TItemType key) const
{
    for(size_t i = 0; i < count(); i++)
    {
        if(items_[i] == key)
            return i;
    }

    return -1;
}


template <typename TItemType>
bool_t List<TItemType>::next(ptr_t* state) const
{
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<size_t>(*state) + 1);
    return reinterpret_cast<size_t>(*state) <= count();
}

template <typename TItemType>
TItemType List<TItemType>::read(ptr_t state) const
{
    return get((size_t)reinterpret_cast<size_t>(state) - 1);
}
}