#pragma once

#include "sly/global.h"

template<typename TType>
struct ref_t
{
	public:
		ref_t() : ref_t(nullptr) {}
		ref_t(ptr_t ptr);
		ref_t(TType& value) { ptr_ = &value; }
		ref_t(const TType& value) { ptr_ = const_cast<TType*>(&value); }
        
        template<typename TOtherType>
        ref_t(ref_t<TOtherType> reference);

		bool_t isEmpty() const;
		TType& get() const;
        TType* ptr() const;
		TType** pptr() const;

		template<typename TOtherType>
        ref_t<TOtherType> as() { return reinterpret_cast<TOtherType*>(ptr_); }

		operator TType&() { return *ptr_; }
		operator TType*() { return ptr_; }
		operator TType**() { return &ptr_; }
		operator void**() { return reinterpret_cast<void**>(&ptr_); }
		TType* operator->() { return ptr_; }
		TType** operator&() { return &ptr_; }
		
		bool_t operator==(TType* ptr) { return ptr == ptr_; }
		
	private:
		TType* ptr_;
	
	
	template<typename TType>
	friend struct out_ptr_t;
	
	template<typename TType>
	friend struct ref_t;
};
template<typename TType>
ref_t<TType>::ref_t(ptr_t ptr) 
{
    ptr_ = reinterpret_cast<TType*>(ptr);
}

template<typename TType>
template<typename TOtherType>
ref_t<TType>::ref_t(ref_t<TOtherType> reference) 
{
    ptr_ = reinterpret_cast<TType*>(reference.ptr());
}

template<typename TType>
bool_t ref_t<TType>::isEmpty() const {
    return ptr() == NULL;
}

template<typename TType>
TType& ref_t<TType>::get() const {
    return *(ptr_);
}

template<typename TType>
TType* ref_t<TType>::ptr() const {
    return ptr_;
}
template<typename TType>
TType** ref_t<TType>::pptr() const {
    return &ptr_;
}
		
