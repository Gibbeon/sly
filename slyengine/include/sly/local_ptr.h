#pragma once

#include "sly/global.h"

template<typename TType>
struct local_ptr_t
{
	public:
		local_ptr_t(ptr_t ptr);
        
        template<typename TOtherType>
        local_ptr_t(ref_t<TOtherType> reference);

		bool_t isEmpty() const;
		TType& get() const;
        TType* ptr() const;

		//operator out_ptr_t<TType>() { return out_ptr_t<TType>(&ptr_); }
		operator ref_t<TType>() { return ref_t<TType>(ptr_); }
		TType* operator->() { return reinterpret_cast<TType*>(ptr_); };
		
	private:
		ptr_t ptr_;

	template<typename TType>
	friend struct out_ptr_t;
};

#include "sly/local_ptr.hpp"
