
template<typename TSource, typename TDestination, typename UnaryFunction>
SelectIterator<TSource, TDestination, UnaryFunction>::SelectIterator(const Enumerable<TSource>* source, UnaryFunction function) : 
    castSource_(source),
    cursor_(NULL),
    function_(function)
{

}

template<typename TSource, typename TDestination, typename UnaryFunction>
TDestination SelectIterator<TSource, TDestination, UnaryFunction>::current() const 
{
    return this->read(NULL);
}

template<typename TSource, typename TDestination, typename UnaryFunction>
bool_t SelectIterator<TSource, TDestination, UnaryFunction>::moveNext() const   
{
    return this->next(NULL);
}

template<typename TSource, typename TDestination, typename UnaryFunction>
TDestination SelectIterator<TSource, TDestination, UnaryFunction>::read(ptr_t state) const
{
    return (TDestination)function_(castSource_->read(cursor_));
}

template<typename TSource, typename TDestination, typename UnaryFunction>
bool_t SelectIterator<TSource, TDestination, UnaryFunction>::next(ptr_t* state) const
{
    return castSource_->next(&cursor_);
}