#pragma once

#include "sly/global.h"
#include "sly/io/binarywriter.h"
#include "sly/io/binaryreader.h"
#include "sly/runtime/typeactivator.h"

#include "sly/runtime/serialization/serializer.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly {
    
    class JSONSerializer : public ISerializer {
    public:
        JSONSerializer(IOutputStream& stream) : _stream(stream), _writer(stream) {}
        virtual ~JSONSerializer() {}

        virtual void write(const TypeInfo& type, vptr_t value, size_t count = 1) {
            start(type);

            if(type.isSerializable()) {
                ISerializable* object = reinterpret_cast<ISerializable*>(value);
                object->serialize(*this);      
            }
            else {
                if(type.isArray()) {
                    _writer.write("[");
                    for(size_t i = 0; i < count; i++) {
                        write(type.getArrayType(), reinterpret_cast<vptr_t>((size_t)value + (i * type.getArrayType().getSize())));
                        _writer.writeline(",");
                    }                    
                    _writer.write("]");
                } else {
                    _writer.write("BINARY DATA");
                    //_writer.write(value, type.getSize());
                    _writer.writeline(",");
                }
            }   

            end();
        }

        virtual void write(const TypeInfo& type, const char* fieldName, vptr_t value, size_t count = 1) {
            _writer.write(fieldName);
            _writer.write(": ");

            write(type, value, count);
        }

    protected:
        virtual void start(const TypeInfo& type) {
            _writer.write(START_RECORD);
        }

        virtual void end() {
            _writer.write(END_RECORD);
        }

        virtual IOutputStream& getStream() { return _stream; }

        IOutputStream& _stream;
        TextWriter _writer;

        const char* START_RECORD = "{";
        const char* END_RECORD = "}";
    };   

    class LuaDeserializer : public IDeserializer {
    public:
        LuaDeserializer(IInputStream& stream, TypeActivator& activator) : _stream(stream), _reader(stream), _activator(activator) {}
        virtual ~LuaDeserializer() {}

        virtual void read(vptr_t buffer, size_t size) {
           /* if(_reader.read<u32>() != START_RECORD) {
                return;
            }

            type_id objectId = _reader.read<type_id>();
            TypeInfo typeInfo = _activator.getTypeInfo(objectId);

            if(!typeInfo.isPolymophic()) {
                _reader.read(buffer, typeInfo.getSize());
            } else {
                vptr_t object = _activator.create(objectId, buffer);                       
            
                if(typeInfo.isSerializable()) {
                    ISerializable* serializable = reinterpret_cast<ISerializable*>(object);
                    serializable->deserialize(*this);
                } else {
                    _reader.read(object, typeInfo.getSize());
                }
            }

            if(_reader.read<u32>() != END_RECORD) {
                 return;   
            } */

                size_t scope = 0;
                while(!_reader.eof())
                {
                    char value = _reader.read<char>();
                    
                    if(value == '{')
                        scope++;
                }
            


        }

    protected:
        virtual IInputStream& getStream() { return _stream; }

        IInputStream& _stream;
        TypeActivator& _activator;
        BinaryReader _reader;
    
        const static u32 START_RECORD = 0xBAD0BEEF;
        const static u32 END_RECORD = 0xDEADF00D;
    };   
}