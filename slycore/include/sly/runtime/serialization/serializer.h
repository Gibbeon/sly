#pragma once

#include "sly/global.h"
#include "sly/io/ostream.h"
#include "sly/runtime/serialization/serializable.h"
#include "sly/runtime/hastypeinfo.h"

namespace sly {

    enum eValue {
        eTest_Value = 1
    };

#define DEFINE_ENUM(x) static const std::pair<const char*, size_t> _ENUM_ ## x[] = 
#define ENUM_VALUE(x) { std::pair<const char*, size_t>(STRINGIFY(x), x) }

DEFINE_ENUM(eValue) {
    ENUM_VALUE(eTest_Value),
};

    
    class IString {
    public:
        virtual const char_t* data() = 0;
        virtual size_t length() = 0;
    };

    template<typename TChar = char_t>
    class BaseString : public IString {
    public:
        BaseString(): _data(NULL) {}
        BaseString(const TChar* data) : _data(data) {}
        virtual ~BaseString() {}

        virtual size_t length() { return TChar* data = data(); size_t index = 0; while(data[index]) { ++index; }; return index; }
        virtual const TChar* data() { return _data; }

    protected:
        const TChar* _data;
    };

    
    template<typename TChar = char_t>
    class BaseMutableString : public IString {
    public:
        BaseMutableString() {
            _string.insert(_string.begin(), (TChar) '\0');
        }
        virtual ~BaseMutableString() {}

        virtual char_t get(size_t index) {
            return _string[index];
        }

        void append(TChar value) {
            _string.insert(_string.end()--, value);
        }

        void set(size_t index, TChar value) {
            _string[index] = value;
        }

        virtual const TChar* data() {
            return (const TChar*)_string.data();
        }

        virtual size_t length() {
            return _string.size() - 1;
        }
    
    protected:
        std::vector<TChar> _string;
    };
   
    using String = BaseString<>;
    using MutableString = BaseMutableString<>;

    class IConvertable {
    public:
        virtual ~IConvertable() {} 

        virtual void toString(const MutableString& string) = 0;
        virtual void fromString(const IString& string) = 0;

        virtual void toStream(IOutputStream& stream) = 0;
        virtual void fromStream(IInputStream& stream) = 0;
    };    

    std::pair<TEnumType, String> tagEnumType_NameValuePairs = {
        eEnumType_Entry1, "eEnumType_Entry1"
    };

    template<enum TEnumType, size_t N>
    class Enum : public IConvertable {
    public:
        Enum() : _value(0) {}
        virtual ~Enum*() {}
        
        virtual void toString(const MutableString& string) = 0;
        virtual void fromString(const IString& string) = 0;

        virtual void toStream(IOutputStream& stream) = 0;
        virtual void fromStream(IInputStream& stream) = 0;

        bool_t hasFlag(TEnumType value);
        bool_t setFlag(TEnumType flag);

        operator TEnumType() { return _value; }
    protected:
        TEnumType _value;

        Array<IString&> _names;
        Array<TEnumType> _values;
    };

    class IConverter {
    public:
        virtual ~IConverter() {} 

        virtual void toString(vptr_t value, size_t length, const MutableString& string) = 0;
        virtual void fromString(const IString& string, vptr_t value, size_t length) = 0;

        virtual void toStream(vptr_t value, size_t length, IOutputStream& stream) = 0;
        virtual void fromStream(IInputStream& stream, vptr_t value, size_t length) = 0;
    };

    class IntegerConverter : public IConverter {
    public:
        IntegerConverter() : _base(10) {

        }

        virtual ~IntegerConverter() {}

        virtual void toString(vptr_t value, size_t length, const MutableString& string) {
            size_t nIndex = 0;
            s64 integer = 0;

            switch(length) {
                case 1: //s8
                    integer = (s64)*(s8*)value; break;
                case 2: //s16
                    integer = (s64)*(s16*)value; break;
                case 4: //s32
                    integer = (s64)*(s32*)value; break;
                case 8: //s64
                    integer = (s64)*(s64*)value; break;
            }

            while(integer > 0) {
                string.append((char_t)('0' + integer % _base));
                integer = integer / _base;
            }
            --length;
        }

        virtual void fromString(const IString& string, vptr_t value, size_t length) {
            s64 integer = 0;
            for(size_t i = 0; i < string.length(); i++) {
                integer += string[i] - '0' * (string.length() - 1) * 10;
            }
            
            memcpy(value, &integer[sizeof(s64)-length], length);
        }

        virtual void toStream(vptr_t value, size_t length, IOutputStream& stream) {
            BinaryWriter writer(stream);
            writer.write(vptr_value, length);
        }

        virtual void fromStream(IInputStream& stream, vptr_t value, size_t length) {    
            BinaryReader reader(stream);
            reader.read(vptr_value, length);
        }

    protected:
        size_t _base;
    };



    class Converter {
    public:
        Enumeration(std::pair<const char*, size_t> values, size_t length) : _values(values), _length(length) {

        }

        const char* getName(size_t value) const {
            for(size_t i = 0; i < _length; i++) {
                if(_values[i].second == value) {
                    return _values[i].first;
                }
            }

            return NULL;
        }

        size_t getValue(const char* name) const {
            for(size_t i = 0; i < _length; i++) {
                if(strcmp(_values[i].first, name) == 0) {
                    return _values[i].second;
                }
            }

            return (size_t)-1;
        }

        std::pair<const char*, size_t>& getAt(size_t index) {
            return _values[index];
        }

    protected:
        std::pair<const char*, size_t>* _values;
        size_t _length;
    };

    class ISerializer {
    public:
        virtual ~ISerializer() {}
        
        virtual void write(const char* name, ISerializable& value) = 0;
        virtual void write(const char* name, u32 value) = 0;
        virtual void write(const char* name, Enum value) = 0;

    protected:
        ISerializer() {}
    };    

    class IDeserializer {
    public:
        virtual ~IDeserializer() {}

        virtual void read(ISerializable *value) = 0;

    protected:
        IDeserializer() {}
    };
}