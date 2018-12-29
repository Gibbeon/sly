template <typename TItemType>
Array<TItemType>::Array(const TItemType* items, s32 count)
{
    init(const_cast<TItemType*>(items), count);
}

template <typename TItemType>
Array<TItemType>::Array(TItemType* items, s32 count)
{
    init(items, count);
}

template <typename TItemType>
void Array<TItemType>::init(TItemType* items, s32 count)
{
    items_ = items;
    count_ = count;
}

template <typename TItemType>
void Array<TItemType>::set(s32 index, const TItemType item)
{
    BOUNDS_CHECK(count_, index);

    items_[index] = item;
}

template <typename TItemType>
TItemType Array<TItemType>::get(s32 index) const
{
    BOUNDS_CHECK(count_, index);

    return items_[index];
}

template <typename TItemType>       
s32 Array<TItemType>::count() const
{
    return count_;
}

template <typename TItemType>
TItemType& Array<TItemType>::operator[](s32 index)
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
    return get((s32)reinterpret_cast<size_t>(state) - 1);
}