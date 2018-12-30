#pragma once

//#ifndef SLY_FUNCTION_STATIC_BUFFER_SIZE
#define SLY_FUNCTION_STATIC_BUFFER_SIZE 64
//#define SLY_FUNCTION_STATIC_BUFFER_SIZE 32 + (sizeof(Function<TResult(TArgs...)>::ReferenceWrapper*))
//#endif

#include "sly/global.h"
#include "sly/collections/enumerable.h"
#include "sly/collections/array.h"

namespace sly {

    template <typename TItemType>
    class Array;

    template<typename TResult, typename... TArgs>
    class Function;

    template<typename TResult, typename... TArgs>
    class Function<TResult(TArgs...)>
    {
    public:
        class ReferenceWrapper
        {
            public:
                typedef TResult (*TSignature)(TArgs...);

                ReferenceWrapper();
                ReferenceWrapper(const TSignature func);
                                
                virtual TResult exec(TArgs... arguments);
            
            private:
                TSignature fn_;
        };

        template<typename TClass>
        class MemberReferenceWrapper : public ReferenceWrapper
        {
            public:
                MemberReferenceWrapper(TClass& ref);

                virtual TResult exec(TArgs... arguments);
            private:
                TClass& ref_;
        };

        template<typename TClass>
        class InstanceMemberReferenceWrapper : public ReferenceWrapper
        {
            public:
                typedef TResult (TClass::*TSignature)(TArgs...);

                InstanceMemberReferenceWrapper(TClass& object, TSignature method);

                virtual TResult exec(TArgs... arguments);

            private:
                TClass& object_;
                TSignature method_;
        };
    public:
        typedef TResult (*TSignature)(TArgs...);

        Function();
        ~Function();
        Function(const TSignature func);

        template<typename TClass>
        Function(TClass lambda);

        template<typename TClass>
        Function(TClass& instance, TResult (TClass::*method)(TArgs...) );

        Function(const Function& func);
        Function(Function&& func);
        
        TResult operator()(TArgs... arguments) const;
        Function& operator=(const Function& rhs);

        private:
            ReferenceWrapper* getFn() { return reinterpret_cast<ReferenceWrapper*>(buf_); }
            ubyte buf_[SLY_FUNCTION_STATIC_BUFFER_SIZE];
    };


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
    Function<TResult(TArgs...)>::Function()
    { 

    }

    template<typename TResult, typename... TArgs>
    Function<TResult(TArgs...)>::~Function()
    {

    }

    template<typename TResult, typename... TArgs>
    Function<TResult(TArgs...)>::Function(const TSignature func) 
    { 
        new (buf_) ReferenceWrapper(func); 
        //SLYASSERT_TRUE( (void*)this_ == (void*)buf_, "verify me");
    }

    template<typename TResult, typename... TArgs>
    template<typename TClass>
    Function<TResult(TArgs...)>::Function(TClass lambda)
    {
        static_assert (sizeof(MemberReferenceWrapper<TClass>) <= SLY_FUNCTION_STATIC_BUFFER_SIZE);
        new (buf_) MemberReferenceWrapper<TClass>(lambda);
        SLYASSERT_TRUE( (void*)this_ == (void*)buf_, "verify me");
    }

    template<typename TResult, typename... TArgs>
    template<typename TClass>
    Function<TResult(TArgs...)>::Function(TClass& instance, TResult (TClass::*method)(TArgs...) )
    {
        static_assert (sizeof(InstanceMemberReferenceWrapper<TClass>) <= SLY_FUNCTION_STATIC_BUFFER_SIZE);
        new (buf_) InstanceMemberReferenceWrapper<TClass>(instance, method);
    }

    template<typename TResult, typename... TArgs>
    Function<TResult(TArgs...)>::Function(const Function& func) 
    { 
        Enumerable<ubyte>::copy(Array<ubyte>(func.buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE), this->buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE); 
    }

    template<typename TResult, typename... TArgs>
    Function<TResult(TArgs...)>::Function(Function&& func) 
    { 
        Enumerable<ubyte>::copy(Array<ubyte>(func.buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE), this->buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE); 
    }


    template<typename TResult, typename... TArgs>
    Function<TResult(TArgs...)>& Function<TResult(TArgs...)>::operator=(const Function& rhs)
    {
        Enumerable<ubyte>::copy(Array<ubyte>(rhs.buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE), this->buf_, SLY_FUNCTION_STATIC_BUFFER_SIZE);
        return *this;
    }

    template<typename TResult, typename... TArgs>
    TResult Function<TResult(TArgs...)>::operator()(TArgs... arguments) const
    {
        Function<TResult(TArgs...)>::ReferenceWrapper* pFn = reinterpret_cast<Function<TResult(TArgs...)>::ReferenceWrapper*>(const_cast<ubyte*>(buf_));
        return pFn->exec(static_cast<TArgs &&>(arguments)...);
    }
    
    #include "sly/function.hpp"

}
