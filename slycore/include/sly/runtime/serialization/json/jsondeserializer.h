#pragma once

#include <nlohmann/json.hpp>
#include "sly/global.h"
#include "sly/io/iostream.h"
#include "sly/io/textreader.h"
#include "sly/runtime/serializable.h"
#include "sly/runtime/activator.h"
#include "sly/runtime/serialization/deserializer.h"

// for convenience
using json = nlohmann::json;

namespace sly { 
    class JsonDeserializer : public IDeserializer {
    public:
        JsonDeserializer(IInputStream& stream, Activator& activator) : _activator(activator) {
             _data = json::parse(TextReader(stream).readAll());
        }

        JsonDeserializer(json data, Activator& activator) : _data(data), _activator(activator) {

        }

        json data() const {
            return _data;
        }

        virtual size_t size() const {
            if(_data.is_array())
                return _data.size();

            return 1;
        }

        virtual retval<void> read(ISerializable& result) {
            return result.deserialize(*this);       
        } 

        virtual retval<std::unique_ptr<IDeserializer>> array(gsl::czstring<> name) {
            auto elem = _data[name];
            return std::make_unique<JsonDeserializer>(elem, _activator);
        }      

        virtual retval<void> read(gsl::czstring<> name, vptr_t& value, size_t size) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            //value = *(vptr_t)elem.get_ptr();
            return success();
        }       

        virtual retval<void> read(gsl::czstring<> name, uint_t& value) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }  

        virtual retval<void> read(gsl::czstring<> name, f32& value) {
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
            auto des = JsonDeserializer(elem, _activator);
            return value.deserialize(des);        
        }

        virtual retval<void> read(size_t index, vptr_t& value, size_t size) {
            auto elem = _data[index];
            if(elem.is_null()) {
                return failed();
            }
            //value = *(vptr_t)elem.get_ptr();
            return success();
        }       

        virtual retval <void> read(size_t index, uint_t& value) {
            auto elem = _data[index];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }  

        virtual retval <void> read(size_t index, f32& value) {
            auto elem = _data[index];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }  

        virtual retval<void> read(size_t index, std::string& value) {
            auto elem = _data[index];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();

            //return readData<std::string>(name, value);
        }  

        virtual retval<void> read(size_t index, ISerializable& value) {
            auto elem = _data[index];
            if(elem.is_null()) {
                return failed();
            }
            return value.deserialize(JsonDeserializer(elem, _activator));        
        }
        
        virtual retval<std::shared_ptr <ISerializable>> create(gsl::czstring<> type, gsl::czstring<> name) {
            auto result = _activator.create(type);
            read(name, *(result.get()));
            return result;
        }

    protected:
    private:
        json _data;
        Activator& _activator;
    };
}



