template <typename TItemType>
Array<TItemType>::Array(const TItemType* items, size_t count)
{
    init(const_cast<TItemType*>(items), count);
}

template <typename TItemType>
Array<TItemType>::Array(TItemType* items, size_t count)
{
    init(items, count);
}

template <typename TItemType>
void Array<TItemType>::init(TItemType* items, size_t count)
{
    items_ = items;
    count_ = count;
}

template <typename TItemType>
void Array<TItemType>::set(size_t index, const TItemType item)
{
    BOUNDS_CHECK(count_, index);

    items_[index] = item;
}

template <typename TItemType>
TItemType Array<TItemType>::get(size_t index) const
{
    BOUNDS_CHECK(count_, index);

    return items_[index];
}

template <typename TItemType>       
size_t Array<TItemType>::count() const
{
    return count_;
}

template <typename TItemType>
TItemType& Array<TItemType>::operator[](size_t index)
{
    BOUNDS_CHECK(count_, index);
    return items_[index];
}

template <typename TItemType>
TItemType* Array<TItemType>::ptr() const
{
    return items_;
}

template <typename TItemType>
bool_t Array<TItemType>::next(ptr_t* state) const
{
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<size_t>(*state) + 1);
    return reinterpret_cast<size_t>(*state) <= count();
}

template <typename TItemType>
TItemType Array<TItemType>::read(ptr_t state) const
{
    return get((size_t)reinterpret_cast<size_t>(state) - 1);
}