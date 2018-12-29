template <typename TDescType>
ref_t<TDescType> Builder<TDescType>::Build() { 
    return ref_t<TDescType>(&_desc); 
}