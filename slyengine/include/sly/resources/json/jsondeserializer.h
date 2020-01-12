#pragma once

#include <nlohmann/json.hpp>
#include "sly/global.h"
#include "sly/io/iostream.h"
#include "sly/io/textreader.h"
#include "sly/resources/serializable.h"
#include "sly/resources/deserializer.h"

// for convenience
using json = nlohmann::json;

namespace sly { 
    class JsonDeserializer : public IDeserializer {
    public:
        JsonDeserializer(IInputStream& stream) {
            auto data = (const char_t*)TextReader(stream).readAll().c_str();
             //_data = json::parse(data);
             _data = json::parse("{\"name\":\"VSMain\",\"data\":\"struct PSInput { float4 position : SV_POSITION; float4 color : COLOR; }; PSInput VSMain(float4 position : POSITION, float4 color : COLOR) {  PSInput result; result.position = position; result.color = color; return result; }\",\"entryPoint\":\"VSMain\",\"target\":\"vs_5_0\"}");
        }

        virtual size_t size() const {
            return _data.size();
        }

        virtual retval<void> read(gsl::czstring<> name, vptr_t& value, size_t size) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            //value = *(vptr_t)elem.get_ptr();
            return success();
        }  

        virtual retval<void> readInteger(gsl::czstring<> name, uint_t& value) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();
        }  

        virtual retval<void> readString(gsl::czstring<> name, std::string& value) {
            auto elem = _data[name];
            if(elem.is_null()) {
                return failed();
            }
            value = elem.get<std::remove_reference<decltype(value)>::type>();
            return success();

            //return readData<std::string>(name, value);
        }  

        virtual retval<void> readObject(gsl::czstring<> name, ISerializable& result) {
            result.deserialize(*this);            
            return success();
        }

    protected:
    private:
        json _data;
    };
}



