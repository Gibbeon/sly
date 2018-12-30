template <typename TItemType, typename TCollectionType>
void Queue<TItemType, TCollectionType>::enqueue(const TItemType item)
{
    list_.add(item);
}

template <typename TItemType, typename TCollectionType>
TItemType Queue<TItemType, TCollectionType>::dequeue()
{
    TItemType temp = list_[0];
    list_.remove(0);
    return temp;
}

template <typename TItemType, typename TCollectionType>
size_t Queue<TItemType, TCollectionType>::count() const
{
    return list_.count();
}

template <typename TItemType, typename TCollectionType>
TItemType Queue<TItemType, TCollectionType>::peek() const
{
    return list_.get(0);
}

template <typename TItemType, typename TCollectionType>
bool_t Queue<TItemType, TCollectionType>::next(ptr_t* state) const
{
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<size_t>(*state) + 1);
    return reinterpret_cast<size_t>(*state) <= count();
}

template <typename TItemType, typename TCollectionType>
TItemType Queue<TItemType, TCollectionType>::read(ptr_t state) const
{
    return list_.get(reinterpret_cast<size_t>(state) - 1);
}