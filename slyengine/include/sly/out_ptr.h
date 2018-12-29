#pragma once

#include "sly/global.h"

template<typename TType>
struct out_ptr_t
{
	public:
		out_ptr_t(ptr_t ptr);
        
        template<typename TOtherType>
        out_ptr_t(ref_t<TOtherType> reference);

		bool_t isEmpty() const;
		TType& get() const;
        TType* ptr() const;
		
	private:
		ptr_t ptr_;
};

#include "sly/out_ptr.hpp"
