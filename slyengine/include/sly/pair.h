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

	#include "sly/pair.hpp"
}
