template <typename TItemType>
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
void FixedArray<TItemType>::set(s32 index, const TItemType item)
{
    BOUNDS_CHECK(Length, index);

    items_[index] = item;
}

template <typename TItemType>
TItemType FixedArray<TItemType>::get(s32 index) const
{
    BOUNDS_CHECK(Length, index);

    return items_[index];
}

template <typename TItemType>       
s32 FixedArray<TItemType>::count() const
{
    return Length;
}

template <typename TItemType>
TItemType& FixedArray<TItemType>::operator[](s32 index)
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
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<s32>(*state) + 1);
    return reinterpret_cast<s32>(*state) <= Length;
}

template <typename TItemType>
TItemType FixedArray<TItemType>::read(ptr_t state) const
{
    return get(reinterpret_cast<s32>(state) - 1);
}