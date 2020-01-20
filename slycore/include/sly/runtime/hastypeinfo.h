#pragma once

#include "sly/runtime/types.h"
#include "sly/runtime/typeinfo.h"

namespace sly {

}

//#define _GET_TYPE_INFO()     virtual const sly::TypeInfo& getType() { static const sly::TypeInfo instance = sly::TypeInfo::get<std::remove_reference<decltype(*this)>::type>(); return instance; }

