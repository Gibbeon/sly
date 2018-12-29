template <typename T>
Min<T>::Min() : 
    assigned_(false) 
{

}

template <typename T>
Min<T>::Min(T value) : 
    assigned_(true), 
    value_(value) 
{

}

template <typename T>
Min<T>::Min(const Min& copy) : 
    assigned_(copy.assigned_), 
    value_(copy.value_) 
{

}

template <typename T>
void Min<T>::accumulate(T value)
{
    if(!assigned_) 
    { 
        value_ = value; 
        assigned_ = TRUE;
    } 
    else 
    {
        value_ = Math::min(value_, value);
    } 
}

template <typename T>
Min<T>::operator T() const 
{ 
    return value(); 
}

template <typename T>
T Min<T>::operator*() const 
{ 
    return value(); 
}

template <typename T>
Min<T>& Min<T>::operator=(Min& rhs)
{
    this->assigned_ = rhs.assigned_;
    this->value_ = rhs.value_;
}

template <typename T>
Min<T>& Min<T>::operator+=(T value) 
{
    accumulate(value);
    return *this;
}

template <typename T>
T Min<T>::value() const 
{
    SLYASSERT_TRUE(isDefined(), "Cannot retrieve a value of a min structure if it has never been set."); 
    return value_; 
}

template <typename T>
bool_t Min<T>::isDefined() const 
{ 
    return assigned_; 
}

template <typename T>
Min<T> Min<T>::calculate(Enumerable<T> array)
{
    Min result;
    array.foreach([&](T value) { result += value; });
    return result;
}