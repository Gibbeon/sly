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
        JsonDeserializer(IInputStream& stream, Activator& activator = Activator()) : JsonDeserializer(json::parse(TextReader(stream).readAll()), activator) {}
        JsonDeserializer(std::string& data, Activator& activator = Activator())  : JsonDeserializer(json::parse(data.c_str()), activator) { }    
        JsonDeserializer(gsl::czstring<> data, Activator& activator = Activator())  : JsonDeserializer(json::parse(data), activator) { }
        JsonDeserializer(vptr_t data, size_t size, Activator& activator = Activator()) : JsonDeserializer(json::parse((char_t*)data), activator) {}
        JsonDeserializer(json data, Activator& activator = Activator()) : _activator(activator) {
            _data.push_back(data);
        }

        virtual ~JsonDeserializer() {}

        virtual size_t size() {
            if(data().is_array())
                return data().size();
                
            if(data().is_null())
                return 0;

            return 1;
        }
 
        json& data() { return _data.back(); }

         //integer
        virtual retval<void> read(u8& value, u8 default) {
            return readValue(value, default);
        }
        virtual retval<void> read(u16& value, u16 default){
            return readValue(value, default);
        }
        virtual retval<void> read(u32& value, u32 default){
            return readValue(value, default);
        }
        virtual retval<void> read(u64& value, u64 default){
            return readValue(value, default);
        }
        virtual retval<void> read(s8& value, s8 default){
            return readValue(value, default);
        }
        virtual retval<void> read(s16& value, s16 default){
            return readValue(value, default);
        }
        virtual retval<void> read(s32& value, s32 default){
            return readValue(value, default);
        }
        virtual retval<void> read(s64& value, s64 default) {
            return readValue(value, default);
        }
        
        //floating point
        virtual retval<void> read(f32& value, f32 default) {
            return readValue(value, default);
        }
        virtual retval<void> read(f64& value, f64 default) {
            return readValue(value, default);
        }
        virtual retval<void> read(f80& value, f80 default) {
            return readValue(value, default);
        }

        //boolean
        virtual retval<void> read(bool_t& value, bool_t default) {
            return readValue(value, default);
        }

        //strings
        virtual retval<void> read(std::string& value, std::string default){
            return readValue(value, default);
        }

        virtual retval<void> read(ISerializable& value) {
            if(data().is_null()) {
                _data.pop_back();
                return failed();
            }

            Expects(data().is_object());

            auto result = value.deserialize(*this);              
            _data.pop_back(); 

            if(!result.succeeded()) {
                return failed();
            }

            return success();
        }

        virtual retval<size_t> read(vptr_t buffer, size_t size) {
            Base64 decoder;
            
            auto elem = data();
            _data.pop_back();

            if(elem.is_null()) {
                return failed<size_t>();
            }

            std::string value = elem.get<std::string>();  

            auto decoded = decoder.decode(value.c_str(), value.length(), (char_t*)buffer, size);

            if(!decoded.succeeded()) {
                return failed<size_t>();
            }

            return decoded.result();
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
            Expects(data().is_object());
            _data.push_back(data()[name]);           
            Ensures(data().is_array() || data().is_null());
            return *this;
        }

        virtual retval<void>    close() {
            _data.pop_back();
            return success();
        }

        //activator
        virtual retval<ISerializable&> create() {
            std::string type;
            if(property("type").read(type).succeeded()) {
                return create(type.c_str());
            }

            return failed<ISerializable&>();
        }

        virtual retval<ISerializable&> create(gsl::czstring<> type) {
            ISerializable* result;
            auto retval = _activator.create<ISerializable>(type, result);

            if(retval.succeeded()) {
                auto value = read(*result);
                if(value.succeeded()) {
                    return *result;
                }
            }
            

            return failed<ISerializable&>();         
        }


    private:
        template<typename TValueType>
        retval<void> readValue(TValueType& value, TValueType default) {
            auto elem = data();
            _data.pop_back();

            if(elem.is_null()) {
                value = default;
                return failed();
            }

            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }

        std::vector<json> _data;     
        Activator& _activator;
    };
}
    


