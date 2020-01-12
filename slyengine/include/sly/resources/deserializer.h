#pragma once

#include "sly/global.h"

namespace sly { 
    class IDeserializer {
    public:
        virtual ~IDeserializer() {}

        virtual size_t size() const = 0;
        
        virtual retval<void> read(gsl::czstring<> name, vptr_t& value, size_t size)  = 0;
        virtual retval<void> readInteger(gsl::czstring<> name, uint_t& value)  = 0;
        virtual retval<void> readString(gsl::czstring<> name, std::string& value)  = 0;
        virtual retval<void> readObject(gsl::czstring<> name, ISerializable& result) = 0;

    protected:
        IDeserializer() {}
    };
}



