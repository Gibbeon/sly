template <typename TItemType>
Iterator<TItemType>::Iterator(const Enumerable<TItemType>* source) :
        cursor_(NULL),
        source_(source)
{
    
}

template <typename TItemType>
TItemType Iterator<TItemType>::operator*() const
{
    return this->current();
}

template <typename TItemType>
bool_t Iterator<TItemType>::operator++() const
{
    return this->moveNext();
}

template <typename TItemType>
bool_t Iterator<TItemType>::moveNext() const
{
    return this->next(NULL);
}

template <typename TItemType>
TItemType Iterator<TItemType>::current() const 
{
    return this->read(NULL);
}

template <typename TItemType>
bool_t Iterator<TItemType>::next(ptr_t* state) const
{
    return source_->next(&cursor_);
}

template <typename TItemType>
TItemType Iterator<TItemType>::read(ptr_t state) const
{
    return source_->read(cursor_);
}
