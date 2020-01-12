#pragma once

#include <nlohmann/json.hpp>
#include "sly/global.h"
#include "sly/io/iostream.h"
#include "sly/io/textreader.h"
#include "sly/runtime/serializable.h"
#include "sly/runtime/serialization/deserializer.h"

// for convenience
using json = nlohmann::json;

namespace sly { 
    class JsonDeserializer : public IDeserializer {
    public:
        JsonDeserializer(IInputStream& stream) {
             _data = json::parse(TextReader(stream).readAll());
        }

        JsonDeserializer(json data) : _data(data) {

        }

        virtual size_t size() const {
            if(_data.is_array())
                return _data.size();

            return 1;
        }

        json data() const {
            return _data;
        }

        virtual retval<void> read(gsl::czstring<> name, vptr_t& value, size_t size) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            //value = *(vptr_t)elem.get_ptr();
            return success();
        } 

        virtual retval<void> read(ISerializable& result) {
            return result.deserialize(*this);       
        }          

        virtual retval<void> read(gsl::czstring<> name, uint_t& value) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }  

        virtual retval<void> read(gsl::czstring<> name, std::string& value) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();

            //return readData<std::string>(name, value);
        }  

        virtual retval<void> read(gsl::czstring<> name, ISerializable& value) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            return value.deserialize(JsonDeserializer(elem));        
        }

    protected:
    private:
        json _data;
    };
}



