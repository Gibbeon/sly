#pragma once

#include "sly/global.h"

template<typename TType>
struct out_ptr_t
{
	public:
		out_ptr_t(ptr_t ptr);
		out_ptr_t(local_ptr_t<TType>& ptr);
        
        template<typename TOtherType>
        out_ptr_t(ref_t<TOtherType> reference);

		bool_t isEmpty() const;
		TType& get() const;
        TType* ptr() const;

		out_ptr_t<TType>& operator=(TType* ptr) {
			*ptr_ = ptr;
			return *this;
		}
		
	private:
		TType** ptr_;
};

#include "sly/out_ptr.hpp"
