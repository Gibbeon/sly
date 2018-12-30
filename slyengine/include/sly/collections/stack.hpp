template <typename TItemType, typename TCollectionType>
void Stack<TItemType, TCollectionType>::push(const TItemType item)
{
    list_.add(item);
}

template <typename TItemType, typename TCollectionType>
TItemType Stack<TItemType, TCollectionType>::pop()
{
    TItemType temp = list_[list_.count()-1];
    list_.remove(list_.count()-1);
    return temp;
}

template <typename TItemType, typename TCollectionType>
size_t Stack<TItemType, TCollectionType>::count() const
{
    return list_.count();
}

template <typename TItemType, typename TCollectionType>
TItemType Stack<TItemType, TCollectionType>::peek() const
{
    return list_.get(list_.count()-1);
}

template <typename TItemType, typename TCollectionType>
bool_t Stack<TItemType, TCollectionType>::next(ptr_t* state) const
{
    *state = reinterpret_cast<ptr_t>(reinterpret_cast<size_t>(*state) + 1);
    return reinterpret_cast<size_t>(*state) <= count();
}

template <typename TItemType, typename TCollectionType>
TItemType Stack<TItemType, TCollectionType>::read(ptr_t state) const
{
    return list_.get(count() - reinterpret_cast<size_t>(state));
}