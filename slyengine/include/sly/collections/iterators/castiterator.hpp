
template<typename TSource, typename TDestination>
CastIterator<TSource, TDestination>::CastIterator(const Enumerable<TSource>* source) : 
    castSource_(source),
    cursor_(NULL)
{

}

template<typename TSource, typename TDestination>
TDestination CastIterator<TSource, TDestination>::current() const 
{
    return this->read(NULL);
}

template<typename TSource, typename TDestination>
bool_t CastIterator<TSource, TDestination>::moveNext() const 
{
    return this->next(NULL);
}

template<typename TSource, typename TDestination>
TDestination CastIterator<TSource, TDestination>::read(ptr_t state) const
{
    return (TDestination)(castSource_->read(cursor_));
}

template<typename TSource, typename TDestination>
bool_t CastIterator<TSource, TDestination>::next(ptr_t* state) const
{
    return castSource_->next(&cursor_);
}