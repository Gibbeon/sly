template <typename TItemType>
List<TItemType>::List() : 
    List(25)
{

}

template <typename TItemType>
List<TItemType>::List(s32 capacity) :
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
s32 List<TItemType>::add(const TItemType item)
{
    addRange(&item, 1);
    return count_;
}

template <typename TItemType>
void List<TItemType>::addRange(const TItemType* array, s32 count)
{
    NOT_NULL(array);

    ensure(count_ + count);
    Memory::copy(array, &items_[count_], sizeof(TItemType) * count);
    count_ += count;
}

template <typename TItemType>
void List<TItemType>::insert(s32 index, const TItemType item)
{
    insertRange(index, &item, 1);
}

template <typename TItemType>
void List<TItemType>::insertRange(s32 index, const TItemType* array, s32 count)
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
void List<TItemType>::remove(s32 index)
{
    BOUNDS_CHECK(count_, index);

    if(index < count_) // ignore if tail
    {
        Memory::copy(&items_[index + 1], &items_[index], sizeof(TItemType) * (count_ - index));
    }
    --count_;
}

template <typename TItemType>
void List<TItemType>::set(s32 index, const TItemType item)
{
    BOUNDS_CHECK(count_, index);

    items_[index] = item;
}

template <typename TItemType>
TItemType List<TItemType>::get(s32 index) const
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
void List<TItemType>::ensure(s32 length)
{
    if(length > capacity_)
    {
        resize(((length + growBy_) - 1 / growBy_) * growBy_);
    }
}

template <typename TItemType>       
s32 List<TItemType>::count() const
{
    return count_;
}

template <typename TItemType>
s32 List<TItemType>::capacity() const
{
    return capacity_;
}

template <typename TItemType>
void List<TItemType>::resize(s32 capacity)
{
    TItemType* newArray = reinterpret_cast<TItemType*>(Memory::allocate(sizeof(TItemType) * capacity));
    
    if(capacity_ > 0)
    {
        Memory::copy(items_, newArray, Math::min(capacity_, capacity));
        Memory::free(items_);
    }
    items_ = newArray;
    capacity_ = capacity;
}

template <typename TItemType>
TItemType& List<TItemType>::operator[](s32 index)
{
    BOUNDS_CHECK(count_, index);
    return items_[index];
}

template <typename TItemType>
TItemType List<TItemType>::operator[](s32 index) const
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
s32 List<TItemType>::indexOf(TItemType key) const
{
    for(s32 i = 0; i < count(); i++)
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
    return get((s32)reinterpret_cast<size_t>(state) - 1);
}