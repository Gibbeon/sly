
template<typename TItemType>
RangeIterator<TItemType>::RangeIterator(const Enumerable<TItemType>* source, s32 skip, s32 take) : 
    Iterator<TItemType>(source),
    skip_(skip),
    take_(skip + ((u32)take)),
    index_(0)
{
    SLYASSERT_GE(skip, 0, "You must skip positive numbers.");
}

template<typename TItemType>
TItemType RangeIterator<TItemType>::current() const 
{
    return this->read(NULL);
}

template<typename TItemType>
bool_t RangeIterator<TItemType>::moveNext() const 
{
    return this->next(&index_);
}

template<typename TItemType>
TItemType RangeIterator<TItemType>::read(ptr_t state) const
{
    return Iterator<TItemType>::read(NULL);
}

template<typename TItemType>
bool_t RangeIterator<TItemType>::next(ptr_t* state) const
{   
    s32 index = (s32)*state;
    while(++index < skip_ && Iterator<TItemType>::next(NULL));
    bool_t retVal = ++index >= skip_ && index <= take_ && Iterator<TItemType>::next(NULL);
    *state = index;
    return retVal;
}