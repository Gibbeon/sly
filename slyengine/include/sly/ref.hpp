template<typename TType>
ref_t<TType>::ref_t(ptr_t ptr) 
{
    ptr_ = ptr;
}

template<typename TType>
template<typename TOtherType>
ref_t<TType>::ref_t(ref_t<TOtherType> reference) 
{
    ptr_ = reinterpret_cast<TType*>(reference.ptr());
}

template<typename TType>
bool_t ref_t<TType>::isEmpty() const {
    return ptr() == NULL;
}

template<typename TType>
TType& ref_t<TType>::get() const {
    return *(ptr());
}

template<typename TType>
TType* ref_t<TType>::ptr() const {
    return reinterpret_cast<TType*>(ptr_);
}
		