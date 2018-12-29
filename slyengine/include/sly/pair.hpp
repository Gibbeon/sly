template<typename TKeyType, typename TValueType>
Pair<TKeyType, TValueType>::Pair()
{

}

template<typename TKeyType, typename TValueType>
Pair<TKeyType, TValueType>::Pair(TKeyType key, TValueType value)
{
    this->key = key;
    this->value = value;
}
