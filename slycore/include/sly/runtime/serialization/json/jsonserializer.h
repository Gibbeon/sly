#pragma once

#include <nlohmann/json.hpp>
#include "sly/global.h"
#include "sly/io/iostream.h"
#include "sly/io/textwriter.h"
#include "sly/runtime/serializable.h"
#include "sly/runtime/serialization/serializer.h"

// for convenience
using json = nlohmann::json;

namespace sly { 
    class JsonSerializer : public ISerializer {
    public:
        JsonSerializer(IOutputStream& stream) : _data({}), _stream(stream), _position(stream.position()) {
             
        }

        JsonSerializer(IOutputStream& stream, json data) : _stream(stream), _data(data), _position(stream.position()) {
             
        }

        virtual ~JsonSerializer() {}

        json data() const {
            return _data;
        }

        virtual retval<void> close() {
            _stream.setPosition(_position);
            TextWriter w(_stream);
            w.write(_data.dump());
            return success();
        }

        virtual retval<void> write(ISerializable& result) {
            auto serializer = JsonSerializer(_stream, _data);
            result.serialize(serializer);
            _data = serializer.data();
            return success();
        }

        virtual retval<void> write(gsl::czstring<> name, uint_t& value)  {
            _data[name] = value;
            return success();
        }

        virtual retval<void> write(gsl::czstring<> name, std::string& value) {
            _data[name] = value;
            return success();            
        }

        virtual retval<void> write(gsl::czstring<> name, gsl::czstring<> value) {
            _data[name] = value;
            return success();            
        }

        virtual retval<void> write(gsl::czstring<> name, vptr_t& value, size_t size) {
            //_data[name] = value; base64_encode
            return failed();            
        }

        virtual retval<void> write(gsl::czstring<> name, ISerializable& result) {
            _data[name] = {};
            result.serialize(JsonSerializer(_stream, _data[name]));
            return success();
        }
       
    protected:
    private:
        json _data;
        IOutputStream& _stream;
        size_t _position;
    };
}



