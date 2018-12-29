

template <typename T>
Average<T>::Average() : 
    count_(0),
    value_(0)
{

}

template <typename T>
Average<T>::Average(T value, s32 count) : 
    count_(count), 
    value_(value) 
{

}

template <typename T>
Average<T>::Average(const Average& copy) : 
    count_(copy.count_), 
    value_(copy.value_) 
{

}

template <typename T>
void Average<T>::accumulate(T value)
{
    ++count_;
    value_ = value_ + (value - value_)/count_;
}

template <typename T>
Average<T>::operator T() const 
{ 
    return value(); 
}

template <typename T>
T Average<T>::operator*() const 
{ 
    return value(); 
}

template <typename T>
Average<T>& Average<T>::operator=(Average& rhs)
{
    this->count_ = rhs.count_;
    this->value_ = rhs.value_;
    return *this;
}

template <typename T>
Average<T>& Average<T>::operator+=(T value) 
{
    accumulate(value);
    return *this;
}

template <typename T>
T Average<T>::value() const 
{
    SLYASSERT_TRUE(isDefined(), "Cannot retrieve a value of a Average structure if it has never been set."); 
    return value_; 
}

template <typename T>
s32 Average<T>::count() const 
{ 
    return count_; 
}

template <typename T>
bool_t Average<T>::isDefined() const 
{ 
    return count_ > 0; 
}

template <typename T>
Average<T> Average<T>::calculate(Enumerable<T> array)
{
    Average result;
    array.foreach([&](T value) { result += value; });
    return result;
}