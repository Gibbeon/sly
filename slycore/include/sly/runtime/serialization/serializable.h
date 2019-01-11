#pragma once

#include "sly/global.h"

namespace sly {
    
        class ISerializable {
            virtual TYPE_ID getTypeId();

            virtual void write(ISerializer&) = 0;
            virtual void read(IDeserializer&) = 0;

        };
}