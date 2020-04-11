#pragma once

#include "sly/global.h"

namespace sly { 
    class IDeserializer {
    public:
        virtual ~IDeserializer() {}
        virtual size_t size() const = 0;
        
        virtual retval<void> read(ISerializable& result) = 0;
        virtual retval<std::unique_ptr<IDeserializer>> array(gsl::czstring<> name) = 0;

        virtual retval<void> read(gsl::czstring<> name, uint_t& value)  = 0;
        virtual retval<void> read(gsl::czstring<> name, f32& value)  = 0;
        virtual retval<void> read(gsl::czstring<> name, std::string& value)  = 0;
        virtual retval<void> read(gsl::czstring<> name, vptr_t& value, size_t size)  = 0;
        virtual retval<void> read(gsl::czstring<> name, ISerializable& result) = 0;

        virtual retval<void> read(size_t index, uint_t& value)  = 0;
        virtual retval<void> read(size_t index, f32& value)  = 0;
        virtual retval<void> read(size_t index, std::string& value)  = 0;
        virtual retval<void> read(size_t index, vptr_t& value, size_t size)  = 0;
        virtual retval<void> read(size_t index, ISerializable& result) = 0;
        
        virtual retval<std::shared_ptr <ISerializable>> create(gsl::czstring<> type, gsl::czstring<> name) = 0;

    protected:
        IDeserializer() {}
    };
}



