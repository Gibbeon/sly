template<typename TType>
local_ptr_t<TType>::local_ptr_t(ptr_t ptr) 
{
    ptr_ = ptr;
}

template<typename TType>
template<typename TOtherType>
local_ptr_t<TType>::local_ptr_t(ref_t<TOtherType> reference) 
{
    ptr_ = reinterpret_cast<TType*>(reference.ptr());
}

template<typename TType>
bool_t local_ptr_t<TType>::isEmpty() const {
    return ptr() == NULL;
}

template<typename TType>
TType& local_ptr_t<TType>::get() const {
    return *(ptr());
}

template<typename TType>
TType* local_ptr_t<TType>::ptr() const {
    return reinterpret_cast<TType*>(ptr_);
}
		