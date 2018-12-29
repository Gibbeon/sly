template <typename TKeyType, typename TItemType, typename TCollectionType>
Map<TKeyType, TItemType, TCollectionType>::Map()
{

}

template <typename TKeyType, typename TItemType, typename TCollectionType>
void Map<TKeyType, TItemType, TCollectionType>::add(const TKeyType key, const TItemType value)
{ 
    list_.add(Pair<TKeyType, TItemType>(key, value));
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
void Map<TKeyType, TItemType, TCollectionType>::remove(const TKeyType key)
{
    list_.remove(indexOf(key));
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
TItemType Map<TKeyType, TItemType, TCollectionType>::get(const TKeyType key) const
{
    return list_.get(indexOf(key)).value;
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
void Map<TKeyType, TItemType, TCollectionType>::set(const TKeyType key, const TItemType value)
{
    list_.set(indexOf(key), Pair<TKeyType, TItemType>(key, value));
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
TItemType& Map<TKeyType, TItemType, TCollectionType>::operator[](const TKeyType key)
{
    return list_[indexOf(key)].value;
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
void Map<TKeyType, TItemType, TCollectionType>::clear()
{
    list_.clear();
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
s32 Map<TKeyType, TItemType, TCollectionType>::count() const
{
    return list_.count();
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
s32 Map<TKeyType, TItemType, TCollectionType>::indexOf(TKeyType key) const
{
    for(s32 i = 0; i < list_.count(); i++)
    {
        if(list_[i].key == key)
            return i;
    }

    return -1;
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
bool_t Map<TKeyType, TItemType, TCollectionType>::next(ptr_t* state) const
{
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<size_t>(*state) + 1);
    return reinterpret_cast<size_t>(*state) <= count();
}

template <typename TKeyType, typename TItemType, typename TCollectionType>
Pair<TKeyType, TItemType> Map<TKeyType, TItemType, TCollectionType>::read(ptr_t state) const
{
    return list_.get((s32)reinterpret_cast<size_t>(state) - 1);
}
