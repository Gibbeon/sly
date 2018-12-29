

template <typename T>
Variance<T>::Variance() : 
    count_(0),
    value_(0),
    mean_(0)
{

}

template <typename T>
Variance<T>::Variance(T value, T mean, s32 count) : 
    mean_(mean), 
    value_(value),
    count_(count)
{

}

template <typename T>
Variance<T>::Variance(const Variance& copy) : 
    mean_(copy.mean_), 
    value_(copy.value_),
    count_(copy.count_)
{

}

template <typename T>
void Variance<T>::accumulate(T value)
{
    count_++;

    T oldMeanValue = mean_;
    mean_ = mean_ + (value - mean_)/count_;
    value_ = count_ > 1 ? value_ + (value - oldMeanValue)*(value - mean_) : 0;
}

template <typename T>
Variance<T>::operator T() const 
{ 
    return value(); 
}

template <typename T>
T Variance<T>::operator*() const 
{ 
    return value(); 
}

template <typename T>
Variance<T>& Variance<T>::operator=(Variance& rhs)
{
    this->mean_ = rhs.mean_;
    this->value_ = rhs.value_;
    this->count_ = rhs.count_;
}

template <typename T>
Variance<T>& Variance<T>::operator+=(T value) 
{
    accumulate(value);
    return *this;
}

template <typename T>
T Variance<T>::value() const 
{
    SLYASSERT_TRUE(isDefined(), "Cannot retrieve a value of a Variance structure if it has never been set."); 
    return value_/(count_ - 1);
}

template <typename T>
T Variance<T>::stddev() const 
{
    return Math::sqrt((float)value()); 
}

template <typename T>
s32 Variance<T>::count() const 
{ 
    return count_; 
}

template <typename T>
bool_t Variance<T>::isDefined() const 
{ 
    return count_ > 1; 
}

template <typename T>
Variance<T> Variance<T>::calculate(Enumerable<T> array)
{
    Variance result;
    array.foreach([&](T value) { result += value; });
    return result;
}