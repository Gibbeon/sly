template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::ReferenceWrapper::ReferenceWrapper() :
    fn_(NULL)
{ 
     
}

template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::ReferenceWrapper::ReferenceWrapper(const TSignature func) :
    fn_(func)
{ 
    
}

template<typename TResult, typename... TArgs>
TResult Function<TResult(TArgs...)>::ReferenceWrapper::exec(TArgs... arguments)
{
    return fn_(static_cast<TArgs &&>(arguments)...);
}

template<typename TResult, typename... TArgs>
template<typename TClass>
Function<TResult(TArgs...)>::MemberReferenceWrapper<TClass>::MemberReferenceWrapper(TClass& ref) : 
    ref_(ref)
{ 

}

template<typename TResult, typename... TArgs>
template<typename TClass>
TResult Function<TResult(TArgs...)>::MemberReferenceWrapper<TClass>::exec(TArgs... arguments)
{
    return ref_(static_cast<TArgs &&>(arguments)...);
}

template<typename TResult, typename... TArgs>
template<typename TClass>
Function<TResult(TArgs...)>::InstanceMemberReferenceWrapper<TClass>::InstanceMemberReferenceWrapper(TClass& object, TSignature method) : 
    object_(object),
    method_(method)
{ 

}

template<typename TResult, typename... TArgs>
template<typename TClass>
TResult Function<TResult(TArgs...)>::InstanceMemberReferenceWrapper<TClass>::exec(TArgs... arguments)
{
    return (object_.*method_)(static_cast<TArgs &&>(arguments)...);
}

template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::Function() : this_(NULL) 
{ 

}

template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::~Function()
{

}

template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::Function(const TSignature func) 
{ 
    this_= new (buf_) ReferenceWrapper(func); 
    SLYASSERT_TRUE( (void*)this_ == (void*)buf_, "verify me");
}

template<typename TResult, typename... TArgs>
template<typename TClass>
Function<TResult(TArgs...)>::Function(TClass lambda)
{
    static_assert (sizeof(MemberReferenceWrapper<TClass>) <= SLY_FUNCTION_STATIC_BUFFER_SIZE);
    this_ = new (buf_) MemberReferenceWrapper<TClass>(lambda);
    SLYASSERT_TRUE( (void*)this_ == (void*)buf_, "verify me");
}

template<typename TResult, typename... TArgs>
template<typename TClass>
Function<TResult(TArgs...)>::Function(TClass& instance, TResult (TClass::*method)(TArgs...) )
{
    static_assert (sizeof(InstanceMemberReferenceWrapper<TClass>) <= SLY_FUNCTION_STATIC_BUFFER_SIZE);
    this_ = new (buf_) InstanceMemberReferenceWrapper<TClass>(instance, method);
}

template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::Function(const Function& func) 
{ 
    this_ = reinterpret_cast<Function<void()>::ReferenceWrapper*>(buf_);



    //Array<ubyte> _test(func.buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE);



    //Enumerable<ubyte>::copy(_test, this->buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE); 

    TODO("Figure this out!");
}

template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>::Function(Function&& func) 
{ 
    this_ = reinterpret_cast<Function<void()>::ReferenceWrapper*>(buf_);
    Enumerable<ubyte>::copy(Array<ubyte>(func.buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE), this->buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE); 
}


template<typename TResult, typename... TArgs>
Function<TResult(TArgs...)>& Function<TResult(TArgs...)>::operator=(const Function& rhs)
{
    //this_ = reinterpret_cast<Function<void()>::ReferenceWrapper*>(buf_);
    //Enumerable<ubyte>::copy(Array<ubyte>(rhs.buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE), this->buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE);
    //return *this;

    TODO("Figure this out!");
    return *this;
}

template<typename TResult, typename... TArgs>
TResult Function<TResult(TArgs...)>::operator()(TArgs... arguments) const
{
    SLYASSERT_NOTNULL(this_, "Unable to execute a null fuction.");

    return this_->exec(static_cast<TArgs &&>(arguments)...);
}