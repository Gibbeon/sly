template <typename TItemType>
Enumerable<TItemType>::operator Iterator<TItemType>() const 
{
    this->getIterator();
}

template <typename TItemType>
Iterator<TItemType> Enumerable<TItemType>::getIterator() const
{
    return Iterator<TItemType>(this);
}

template<typename TItemType>
template<typename TConvertType>
CastIterator<TItemType, TConvertType> Enumerable<TItemType>::cast() const
{
    return CastIterator<TItemType, TConvertType>(this);
}

template <typename TItemType>
TItemType Enumerable<TItemType>::first() const
{
    return first([](TItemType){return TRUE;});
}

template <typename TItemType>
template <typename UnaryFunction>
TItemType Enumerable<TItemType>::first(UnaryFunction lambda) const
{
    auto iter = getIterator();
    while(++iter)
    {
        if(lambda(*iter))
        {
            return *iter;
        }
    }
    
    HALT("Enumerable Failed To Find First");
}
template <typename TItemType>
template <typename UnaryFunction>
WhereIterator<TItemType, UnaryFunction> Enumerable<TItemType>::where(UnaryFunction lambda) const
{
    return WhereIterator<TItemType, UnaryFunction>(this, lambda);
}

template <typename TItemType>
template <typename UnaryFunction>
void Enumerable<TItemType>::foreach(UnaryFunction lambda) const
{
    auto iter = getIterator();
    while(++iter)
    {
        lambda(*iter);
    }
}

template <typename TItemType>
template<typename TConvertType, typename UnaryFunction>
SelectIterator<TItemType, TConvertType, UnaryFunction> Enumerable<TItemType>::select(UnaryFunction lambda) const
{
    return SelectIterator<TItemType, TConvertType, UnaryFunction>(this, lambda);
}

template <typename TItemType>
s32  Enumerable<TItemType>::count() const
{
    s32 result = 0;
    auto iter = getIterator();
    while(++iter)
    {
        ++result;
    }
    return result;
}
template <typename TItemType>
TItemType Enumerable<TItemType>::sum() const
{
    TItemType accumulator = 0;
    auto iter = getIterator();

    while(++iter)
    {
        accumulator += *iter;
    }

    return accumulator;
}

template <typename TItemType>
TItemType Enumerable<TItemType>::min() const
{
    Min<TItemType> min;
    auto iter = getIterator();
    while(++iter)
    {
        min += *iter;
    }
    /*if(++iter)
    {        
        TItemType accumulator = *iter;
        
        while(++iter)
        {
            if(accumulator > *iter)
            {
                accumulator = *iter;
            }
        }
        return accumulator;
    }*/
    
    return min.value();
}

template <typename TItemType>
TItemType Enumerable<TItemType>::max() const
{
    Max<TItemType> max;
    auto iter = getIterator();
    while(++iter)
    {
        max += *iter;
    }

    return max.value();

    /*auto iter = getIterator();

    if(++iter)
    {        
        TItemType accumulator = *iter;
        
        while(++iter)
        {
            if(accumulator > *iter)
            {
                accumulator = *iter;
            }
        }
        return accumulator;
    }
    
    return 0;*/
}
template <typename TItemType>
TItemType Enumerable<TItemType>::average() const
{
    Average<TItemType> avg;
    auto iter = getIterator();
    while(++iter)
    {
        avg += *iter;
    }

    return avg.value();

    /*TItemType   accumulator = 0;
    s32 count = 0;
    auto iter = getIterator();
    while(++iter)
    {
        accumulator += *iter;
        ++count;
    }
    return accumulator / count;*/
}

template <typename TItemType>
bool_t Enumerable<TItemType>::any() const
{
    return any([](TItemType){return TRUE;});
}

template <typename TItemType>
void Enumerable<TItemType>::copy(const Enumerable<TItemType>& src, TItemType* destination, s32 count)
{
    s32 index = 0;
    auto iter = src.getIterator();
    while(++iter && index < count)
    {
        destination[index] = *iter;
        ++index;
    }
}

template <typename TItemType>
void Enumerable<TItemType>::copy(TItemType* destination, s32 count) const
{
    Enumerable<TItemType>::copy(*this, destination, count);
}

template <typename TItemType>
template <typename UnaryFunction>
bool_t Enumerable<TItemType>::any(UnaryFunction lambda) const
{
    auto iter = getIterator();
    while(++iter)
    {
        if(lambda(*iter))
        {
            return TRUE;
        }
    }
    return FALSE;
}

template <typename TItemType>
template <typename UnaryFunction>
bool_t Enumerable<TItemType>::all(UnaryFunction lambda) const
{
    auto iter = getIterator();
    while(++iter)
    {
        if(!lambda(*iter))
        {
            return FALSE;
        }
    }
    return TRUE;
}