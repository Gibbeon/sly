/* template <typename TItemType>
FixedFixedArray<TItemType>::FixedArray(const TItemType* items)
{
    init(const_cast<TItemType*>(items));
}

template <typename TItemType>
FixedArray<TItemType>::FixedArray(TItemType* items)
{
    init(items, count);
}

template <typename TItemType>
void FixedArray<TItemType>::init(TItemType* items)
{
    items_ = items;
}

template <typename TItemType>
void FixedArray<TItemType>::set(size_t index, const TItemType item)
{
    BOUNDS_CHECK(Length, index);

    items_[index] = item;
}

template <typename TItemType>
TItemType FixedArray<TItemType>::get(size_t index) const
{
    BOUNDS_CHECK(Length, index);

    return items_[index];
}

template <typename TItemType>       
size_t FixedArray<TItemType>::count() const
{
    return Length;
}

template <typename TItemType>
TItemType& FixedArray<TItemType>::operator[](size_t index)
{
    BOUNDS_CHECK(Length, index);
    return items_[index];
}

template <typename TItemType>
TItemType* FixedArray<TItemType>::ptr() const
{
    return items_;
}

template <typename TItemType>
bool_t FixedArray<TItemType>::next(ptr_t* state) const
{
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<size_t>(*state) + 1);
    return reinterpret_cast<size_t>(*state) <= Length;
}

template <typename TItemType>
TItemType FixedArray<TItemType>::read(ptr_t state) const
{
    return get(reinterpret_cast<size_t>(state) - 1);
} */