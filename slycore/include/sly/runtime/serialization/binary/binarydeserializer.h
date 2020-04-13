#pragma once

#include "sly/global.h"
#include "sly/io/iostream.h"
#include "sly/runtime/serializable.h"
#include "sly/runtime/activator.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly { 
    /*class BinaryDeserializer : public IDeserializer {
    public:
        BinaryDeserializer(IInputStream& stream, Activator& activator) : _stream(stream), _activator(activator) {}
        virtual ~BinaryDeserializer() {}

        virtual size_t size() {
            TODO();
            return 1;
        }

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
        virtual retval<void> read(std::string& value) {
            u32 size;
            _stream.read(&size, sizeof(size));

            value.resize(size);
            _stream.read(value.data(), size);

            return success();
        }

        //bytes
        virtual retval<void> read(vptr_t buffer, size_t size) {
            _stream.read(buffer, size);
        }

        //objects
        virtual retval<void> read(ISerializable& value) {
            value.deserialize(*this);
        }
        
        virtual IDeserializer&  open(gsl::czstring<> name) {            
            return *this;
        }

        virtual retval<void>    close() {
            return success();
        }

        //parse
        virtual IDeserializer& at(size_t index) {
            return *this;
        }

        virtual IDeserializer& property(gsl::czstring<> name) {
            return *this;
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
            auto result = _activator.create(type);
            
            if(result.succeeded()) {
                auto value = read(result.result());
                if(value.succeeded()) {
                    return result.result();
                }
            }

            return failed<ISerializable&>();       
        }

    protected:
        template<typename TValueType>
        retval<void> readValue(TValueType& value) {
            _stream.read(&value, sizeof(TValueType));
            return success();
        }

        IInputStream& _stream;   
        Activator& _activator;
    };*/
}