#pragma once

#include "sly/global.h"

namespace sly {

	template<typename TKeyType, typename TValueType>
	struct Pair
	{
		public:
			Pair();
			Pair(TKeyType key, TValueType value);

			TKeyType key;
			TValueType value;
	};

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

}
