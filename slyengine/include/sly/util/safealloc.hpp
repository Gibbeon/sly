
template <typename T>
template <typename TArgs...>
SafeAlloc<T>::SafeAlloc(TArgs... args) :
    SafeAlloc<T>::(new T(args))
{

}

template <typename T>
SafeAlloc<T>::SafeAlloc(u32 length) :
    ptr_(new T[length])
{
    
}

template <typename T>
SafeAlloc<T>::SafeAlloc(T* ptr) :
    ptr_(ptr)
{
    
}

template <typename T>
SafeAlloc<T>::~SafeAlloc()
{
    delete ptr_;
}

template <typename T>
T* SafeAlloc<T>::ptr() const
{
    return ptr_;
}

template <typename T>
SafeAlloc<T>::operator T*() const
{
    return ptr_;
}

template <typename T>
T& SafeAlloc<T>::operator*() const
{
    return *ptr_;
}