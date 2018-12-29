#pragma once

#ifndef SLY_FUNCTION_STATIC_BUFFER_SIZE
#define SLY_FUNCTION_STATIC_BUFFER_SIZE 32 + (sizeof(Function<TResult(TArgs...)>::ReferenceWrapper*))
#endif

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
    private:
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
            ReferenceWrapper* this_;
            ubyte buf_[SLY_FUNCTION_STATIC_BUFFER_SIZE];
    };

    #include "sly/function.hpp"

}
