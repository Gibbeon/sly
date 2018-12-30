template<typename TType>
out_ptr_t<TType>::out_ptr_t(ptr_t ptr) 
{
    ptr_ = reinterpret_cast<TType**>(ptr);
}

template<typename TType>
out_ptr_t<TType>::out_ptr_t(local_ptr_t<TType>& ptr) 
{
    ptr_ = reinterpret_cast<TType**>(&ptr.ptr_);
}

template<typename TType>
template<typename TOtherType>
out_ptr_t<TType>::out_ptr_t(ref_t<TOtherType> reference) 
{
    ptr_ = reinterpret_cast<TType**>(&reference.ptr_);
}

template<typename TType>
bool_t out_ptr_t<TType>::isEmpty() const {
    return ptr() == NULL;
}

template<typename TType>
TType& out_ptr_t<TType>::get() const {
    return **(ptr());
}

template<typename TType>
TType* out_ptr_t<TType>::ptr() const {
    return reinterpret_cast<TType*>(*ptr_);
}
		