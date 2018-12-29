#pragma once

#include "sly/global.h"

template<typename TType>
struct ref_t
{
	public:
		ref_t(ptr_t ptr);
        
        template<typename TOtherType>
        ref_t(ref_t<TOtherType> reference);

		bool_t isEmpty() const;
		TType& get() const;
        TType* ptr() const;

		TType* operator->() { return reinterpret_cast<TType*>(ptr_); };
		
	private:
		ptr_t ptr_;
};

#include "sly/ref.hpp"
