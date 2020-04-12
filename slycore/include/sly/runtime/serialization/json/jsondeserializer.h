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
        JsonDeserializer(std::string& data, Activator& activator)  : JsonDeserializer(json::parse(data.c_str()), _activator) { }    
        JsonDeserializer(gsl::czstring<> data, Activator& activator)  : JsonDeserializer(json::parse(data), _activator) { }
        JsonDeserializer(vptr_t data, size_t size, Activator& activator) : JsonDeserializer(json::parse((char_t*)data), _activator) {}
        JsonDeserializer(json data, Activator& activator) : _activator(activator) {
            _data.push_back(data);
        }

        virtual ~JsonDeserializer() {}

        virtual size_t size() {
            if(data().is_array())
                return data().size();

            return 1;
        }
 
        json& data() { return _data.back(); }

         //integer
        virtual retval<void> read(u8& value) {
            return readValue(value);
        }
        virtual retval<void> read(u16& value){
            return readValue(value);
        }
        virtual retval<void> read(u32& value){
            return readValue(value);
        }
        virtual retval<void> read(u64& value){
            return readValue(value);
        }
        virtual retval<void> read(s8& value){
            return readValue(value);
        }
        virtual retval<void> read(s16& value){
            return readValue(value);
        }
        virtual retval<void> read(s32& value){
            return readValue(value);
        }
        virtual retval<void> read(s64& value) {
            return readValue(value);
        }
        
        //floating point
        virtual retval<void> read(f32& value) {
            return readValue(value);
        }
        virtual retval<void> read(f64& value) {
            return readValue(value);
        }
        virtual retval<void> read(f80& value) {
            return readValue(value);
        }

        //boolean
        virtual retval<void> read(bool_t& value) {
            return readValue(value);
        }

        //strings
        virtual retval<void> read(std::string& value){
            return readValue(value);
        }

        virtual retval<void> read(ISerializable& value) {
            Expects(data().is_object());

            auto elem = data();

            if(elem.is_null()) {
                _data.pop_back();
                return failed();
            }

            auto result = value.deserialize(*this);              
            _data.pop_back(); 

            if(!result.succeeded()) {
                return failed();
            }

            return success();
        }

        virtual retval<void> read(vptr_t buffer, size_t size) {
            Base64 decoder;
            
            auto elem = data();
            _data.pop_back();

            if(elem.is_null()) {
                return failed();
            }

            std::string value = elem.get<std::string>();            
            if(!decoder.decode(value.c_str(), value.length(), (char_t*)buffer, size).succeeded()) {
                return failed();
            }

            return success();
        }

        virtual IDeserializer& at(size_t index) {
            Expects(data().is_array());
            _data.push_back(data()[index]);
            return *this;
        }

        virtual IDeserializer& property(gsl::czstring<> name) {
            Expects(data().is_object());

            _data.push_back(data()[name]);
            return *this;            
        }

        virtual IDeserializer&  open(gsl::czstring<> name) {
            return property(name);
        }

        virtual retval<void>    close() {
            _data.pop_back();
            return success();
        }

        virtual retval<ISerializable&> create(gsl::czstring<> type) {
            auto result = _activator.create(type);
            
            if(result.succeeded()) {
                auto value = read(result.result());
                if(value.succeeded()) {
                    return result.result();
                }
            }

            return failed<ISerializable&>();         
        }


    private:
        template<typename TValueType>
        retval<void> readValue(TValueType& value) {
            auto elem = data();
            _data.pop_back();

            if(elem.is_null()) {
                return failed();
            }

            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }

        std::vector<json> _data;     
        Activator& _activator;
    };
}
    


