#pragma once

#include "sly/global.h"
#include "sly/io/binarywriter.h"
#include "sly/io/binaryreader.h"
#include "sly/runtime/typeactivator.h"

#include "sly/runtime/serialization/serializer.h"
#include "sly/runtime/serialization/deserializer.h"

namespace sly {

    class BinarySerializer : public ISerializer {
    public:
        BinarySerializer(IOutputStream& stream) : _stream(stream), _writer(stream) {}
        virtual ~BinarySerializer() {}

        virtual void write(TypeInfo& type, vptr_t data) {
            start(type);

            if(type.isSerializable()) {
                ISerializable* object = reinterpret_cast<ISerializable*>(data);
                object->serialize(*this);      
            }
            else {
                _writer.write(data, type.getSize());
            }
            end();
        }

    protected:
        virtual void start(const TypeInfo& type) {
            _writer.write(START_RECORD);
            _writer.write(type.getId());
        }

        virtual void end() {
            _writer.write(END_RECORD);
        }

        virtual IOutputStream& getStream() { return _stream; }

        IOutputStream& _stream;
        BinaryWriter _writer;

        const static u32 START_RECORD = 0xBAD0BEEF;
        const static u32 END_RECORD = 0xDEADF00D;
    };   

    class BinaryDeserializer : public IDeserializer {
    public:
        BinaryDeserializer(IInputStream& stream, TypeActivator& activator) : _stream(stream), _reader(stream), _activator(activator) {}
        virtual ~BinaryDeserializer() {}

        virtual void read(vptr_t buffer, size_t size) {
            if(_reader.read<u32>() != START_RECORD) {
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