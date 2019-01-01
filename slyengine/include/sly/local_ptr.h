#pragma once

#include "sly/global.h"

template<typename TType>
struct local_ptr_t : public ref_t<TType> {
	public:
		using ref_t::ref_t;
};

/* template<typename TType>
struct local_ptr_t
{
	public:
		local_ptr_t(ptr_t ptr);
        
        template<typename TOtherType>
        local_ptr_t(ref_t<TOtherType> reference);

		bool_t isEmpty() const;
		TType& get() const;
        TType* ptr() const;

		template<typename TOtherType>
        ref_t<TOtherType> as() { return reinterpret_cast<TOtherType*>(ptr_); }

		operator TType*() { return reinterpret_cast<TType*>(ptr_); }
		
		bool_t operator==(TType* ptr) { return ptr == ptr_; }

		operator ref_t<TType>() { return ref_t<TType>(ptr_); }
		TType* operator->() { return reinterpret_cast<TType*>(ptr_); };
		
	private:
		ptr_t ptr_;

	template<typename TType>
	friend struct out_ptr_t;
};

template<typename TType>
local_ptr_t<TType>::local_ptr_t(ptr_t ptr) 
{
    ptr_ = ptr;
}

template<typename TType>
template<typename TOtherType>
local_ptr_t<TType>::local_ptr_t(ref_t<TOtherType> reference) 
{
    ptr_ = reinterpret_cast<TType*>(reference.ptr());
}

template<typename TType>
bool_t local_ptr_t<TType>::isEmpty() const {
    return ptr() == NULL;
}

template<typename TType>
TType& local_ptr_t<TType>::get() const {
    return *(ptr());
}

template<typename TType>
TType* local_ptr_t<TType>::ptr() const {
    return reinterpret_cast<TType*>(ptr_);
}
		 */
