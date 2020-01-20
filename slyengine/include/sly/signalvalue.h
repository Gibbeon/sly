#pragma once

#include "sly/global.h"

namespace sly {

    typedef uint32_t SignalValue;

    static const SignalValue SIGNAL_EMPTY       = (uint32_t) 0;
    static const SignalValue SIGNAL_START       = (uint32_t)-1;
    static const SignalValue SIGNAL_STOP        = (uint32_t)-2;
}


