
template<typename TItemType, typename UnaryFunction>
WhereIterator<TItemType, UnaryFunction>::WhereIterator(const Enumerable<TItemType>* source, UnaryFunction function) : 
    Iterator<TItemType>(source),
    function_(function)
{

}

template<typename TItemType, typename UnaryFunction>
TItemType WhereIterator<TItemType, UnaryFunction>::current() const 
{
    return this->read(NULL);
}

template<typename TItemType, typename UnaryFunction>
bool_t WhereIterator<TItemType, UnaryFunction>::moveNext() const 
{
    return this->next(NULL);
}

template<typename TItemType, typename UnaryFunction>
TItemType WhereIterator<TItemType, UnaryFunction>::read(ptr_t state) const
{
    return Iterator<TItemType>::read(NULL);
}

template<typename TItemType, typename UnaryFunction>
bool_t WhereIterator<TItemType, UnaryFunction>::next(ptr_t* state) const
{
    while(Iterator<TItemType>::next(NULL))
    {
        if(function_(Iterator<TItemType>::read(NULL)))
            return TRUE;
    }

    return FALSE;
}