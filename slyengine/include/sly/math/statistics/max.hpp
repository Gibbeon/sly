

template <typename T>
Max<T>::Max() : 
    assigned_(false) 
{

}

template <typename T>
Max<T>::Max(T value) : 
    assigned_(true), 
    value_(value) 
{

}

template <typename T>
Max<T>::Max(const Max& copy) : 
    assigned_(copy.assigned_), 
    value_(copy.value_) 
{

}

template <typename T>
void Max<T>::accumulate(T value)
{
    if(!assigned_) 
    { 
        value_ = value; 
        assigned_ = TRUE;
    } 
    else 
    {
        value_ = Math::max(value_, value);
    } 
}

template <typename T>
Max<T>::operator T() const 
{ 
    return value(); 
}

template <typename T>
T Max<T>::operator*() const 
{ 
    return value(); 
}

template <typename T>
Max<T>& Max<T>::operator=(Max& rhs)
{
    this->assigned_ = rhs.assigned_;
    this->value_ = rhs.value_;
}

template <typename T>
Max<T>& Max<T>::operator+=(T value) 
{
    accumulate(value);
    return *this;
}

template <typename T>
T Max<T>::value() const 
{
    SLYASSERT_TRUE(isDefined(), "Cannot retrieve a value of a Max structure if it has never been set."); 
    return value_; 
}

template <typename T>
bool_t Max<T>::isDefined() const 
{ 
    return assigned_; 
}

template <typename T>
Max<T> Max<T>::calculate(Enumerable<T> array)
{
    Max result;
    array.foreach([&](T value) { result += value; });
    return result;
}