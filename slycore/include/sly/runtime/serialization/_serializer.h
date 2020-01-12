#pragma once

#include <string>

#include "sly/global.h"
#include "sly/io/outputstream.h"
#include "sly/runtime/serialization/serializable.h"
#include "sly/runtime/hastypeinfo.h"
#include "sly/static_hash.h"

namespace sly {    
    template<typename TType>
    class IConvertTo {
    public:
        virtual void convertTo(TType* value) = 0;
    };

    template<typename TType>
    class IConvertFrom {
    public:
        virtual void convertFrom(TType& value) = 0;
    };

    /*class String {
        public:
            template<typename TChar = char_t>
            String(const TChar* data) :
                _data(data) 
            {

            }

            const TChar* data() { return _data; }

            size_t length() { return _length; }

            u32 getHashCode() {
                return static_hash(_data);
            }

        private:
            const TChar* _data;
    template<typename T>
    class IIterator {
    public:
        virtual T current() = 0;
        virtual bool_t next() = 0;
    private:

    };

    template<typename T>
    class WhereIterator : public IIterator<T> {
    public:
        WhereIterator(IIterator iterator) : _iterator(iterator) {}

        virtual T current() {
            return _iterator.current();
        }

        virtual bool_t next() {
            while(_iterator.next()) {
                if(_fn(_iterator.current())) {
                    return TRUE;
                }
            }
            return FALSE;
        }
    protected:
        IIterator<T> _iterator;
        std::function<bool_t(T& value)> _fn;
    };

    template<typename T>
    class ICollection {
    public:
        typedef IIterator<T> Iterator;

        virtual Iterator getIterator() = 0;

        virtual T& get(size_t index) = 0;
        virtual size_t length() = 0;
    protected:

    };

    template<typename T>
    class Array : public ICollection<T> {
    public:
        Array(const T* data, size_t length) : _data(data), _length(length) {}

        Iterator getIterator() {
            return ArrayIterator(*this);
        }

        virtual T& get(size_t index) {
            return _data[index];
        }

        virtual size_t length() {
            return _length;
        }

    protected:
        T* _data;
        size_t _length;
    };

    template<typename T>
    class ArrayIterator : public IIterator<T> {
        public:
            ArrayIterator(Array<T>& array) : _array(array), _index(-1) {}

            virtual T current() {
                return _array[_index];
            }

            virtual bool_t next() {
                if(_array.length() - 1 == _index) {
                    return FALSE;
                }
                ++_index;
                return TRUE;
            }

        protected:
            Array<T>& _array;
            size_t _index;
        };

    template<typename TChar = char_t>
    class IString : public ICollection<TChar> {
    public:
        virtual ~IString() = default;

        virtual TChar* data() = 0;
        virtual size_t length() = 0;

    protected:
        IString() = default;
    };
    
    template<typename TChar = const char_t>
    class FixedString : public IString<TChar> {
    public:
        FixedString(): _data(NULL) {}
        FixedString(TChar* data) : _data(data) {}

        virtual ~FixedString() {}

    template<typename TChar = char_t>
    class MutableString {
    public:
        MutableString() {
            _string.insert(_string.begin(), (TChar) '\0');
        }

        virtual ~MutableString() {}
        virtual TChar& get(size_t index);
        virtual size_t length() { return _array.length(); }
        virtual const TChar* data() { return _data.data(); }

    protected:
        Array<TChar> _array;
    };
    
    template<typename TChar = char_t>
    class MutableString : public IString<TChar> {
    public:
        MutableString() { }
        MutableString(const TChar* data) : _data(data) {}

        virtual ~MutableString() {}

        void append(TChar value) {
            _string.insert(_string.end()--, value);
        }

        void set(size_t index, TChar value) {
            _string[index] = value;
        }

        MutableString clone();
        FixedString<TChar> substring(size_t start, size_t count);

        virtual const TChar* data() {
            return (const TChar*)_string.c_str();
        }

        virtual size_t length() {
            return _string.size();
        }

        String toString() {
            return String(_string.data(), sizeof(TChar), length());
        }
    
    protected:
        std::vector<TChar> _string;
    };


    
 
        std::basic_string<TChar> _string;
    };

 

    class IConvertable {
    public:
        virtual ~IConvertable() {} 

        virtual void toString(const MutableString<>& string) = 0;
        virtual void fromString(const IString<>& string) = 0;

        virtual void store(IOutputStream& stream) = 0;
        virtual void load(IInputStream& stream) = 0;
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

        static Array<FixedString> _names;
        static Array<TEnumType> _values;
    };

/*
    class IConverter {
    public:
        virtual ~IConverter() {} 

        virtual void toString(vptr_t value, size_t length, const MutableString& string) = 0;
        virtual void fromString(const String& string, vptr_t value, size_t length) = 0;
        virtual void toString(vptr_t value, size_t length, const MutableString<>& string) = 0;
        virtual void fromString(const IString<>& string, vptr_t value, size_t length) = 0;

        virtual void toStream(vptr_t value, size_t length, IOutputStream& stream) = 0;
        virtual void fromStream(IInputStream& stream, vptr_t value, size_t length) = 0;
    };

    class IntegerConverter : public IConverter {
    public:
        IntegerConverter() : _base(10) {

        }

        virtual ~IntegerConverter() {}

        virtual void toString(vptr_t value, size_t length, const MutableString<>& string) {
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

        virtual void fromString(const IString<>& string, vptr_t value, size_t length) {
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
        virtual void write(const char* name, IConvertable& value) = 0;

    protected:
        ISerializer() {}
    };    

    class IDeserializer {
    public:
        virtual ~IDeserializer() {}

        virtual void read(ISerializable *value) = 0;

    protected:
        IDeserializer() {}
    };*/
}
