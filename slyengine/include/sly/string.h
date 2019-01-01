#pragma once

#include "sly/global.h"
#include "sly/sys/memory.h"
#include "sly/collections/array.h"
#include "sly/collections/collection.h"

//intersting note, when count is a static and not a variable from array, there's a pretty large speedup possible due to compiler optimizations
//need to look into fixed array

namespace sly {
    template <typename TChar = char_t>
    class String : public Array<TChar>
    {
        public:
            String();
            String(const TChar* data);
            String(const TChar* data, size_t length);
            String(const String<TChar>& copy);

            String<TChar> substring(size_t offset, size_t length) const;

            bool_t operator ==(const String<TChar> &rhs) const;
            bool_t operator !=(const String<TChar> &rhs) const;
            bool_t operator >(const String<TChar> &rhs) const;
            bool_t operator <(const String<TChar> &rhs) const;
            bool_t operator >=(const String<TChar> &rhs) const;
            bool_t operator <=(const String<TChar> &rhs) const;

            String& operator= (const String<TChar>& x);
            String& operator= (TChar* x);

            explicit operator const TChar*() const;
            
            size_t copy(TChar* buf) const;

            static size_t strlen(const TChar* str);
            static size_t copy(const String<TChar>& src, String<TChar>& dest);
            static size_t compare(const String<TChar>& lhs, const String<TChar>& rhs);
        private:
            
    };


    template <typename TChar>
    String<TChar>::String() :
        String(NULL, 0)
    {

    }

    template <typename TChar>
    String<TChar>::String(const TChar* data) :
        String(data, String::strlen(data))
    {

    }

    template <typename TChar>
    String<TChar>::String(const TChar* data, size_t length) :
        Array<TChar>(data, length)
    {

    }

    template <typename TChar>
    String<TChar>::String(const String<TChar>& copy) :
        Array<TChar>(copy.ptr(), copy.count())
    {

    }

    template <typename TChar>
    String<TChar> String<TChar>::substring(size_t offset, size_t length) const
    {
        return String<TChar>(&Array<TChar>::ptr()[offset], length);
    }

    template <typename TChar>
    size_t String<TChar>::strlen(const TChar* str)
    {
        const TChar* ptr = str;
        if(ptr == 0) return 0;
        while(*(++ptr));
        return (ptr - str) / sizeof(TChar);
    }

    template <typename TChar>
    size_t String<TChar>::copy(const String& src, String& dest)
    {
        size_t length = Math::min(dest.count(), Math::max(src.count(), dest.count()));
        src.copy(dest.ptr(), length);
        dest.count_ = length;
    }

    template <typename TChar>
    size_t String<TChar>::compare(const String& lhs, const String& rhs)
    {
        size_t len = rhs.count();
        
        if(len < lhs.count())
            return -1;
        else if(len > lhs.count())
            return 1;

        size_t fast = len/sizeof(TChar) + 1;
        size_t offset = (fast-1)*sizeof(TChar);
        size_t current_block = 0;

        if( len <= sizeof(TChar)){ fast = 0; }

        TChar *lptr0 = (TChar*)lhs.ptr();
        TChar *lptr1 = (TChar*)rhs.ptr();

        while( current_block < fast ){
        if( (lptr0[current_block] ^ lptr1[current_block] )){
            size_t pos;
            for(pos = current_block*sizeof(TChar); pos < len ; ++pos ){
            if( (lhs.ptr()[pos] ^ rhs.ptr()[pos]) || (lhs.ptr()[pos] == 0) || (rhs.ptr()[pos] == 0) ){
                return  (size_t)((TChar)lhs.ptr()[pos] - (TChar)rhs.ptr()[pos]);
                }
            }
        }

        ++current_block;
        }

        while( len > offset ){
        if( (lhs.ptr()[offset] ^ rhs.ptr()[offset] )){ 
            return (size_t)((TChar)lhs.ptr()[offset] - (TChar)rhs.ptr()[offset]); 
            }
        ++offset;
        }

        return 0;
    }

    template <typename TChar>
    bool_t String<TChar>::operator ==(const String<TChar>& rhs) const
    {
        return compare(*this, rhs) == 0;
    }

    template <typename TChar>
    bool_t String<TChar>::operator !=(const String<TChar>& rhs) const
    {
    return compare(*this, rhs) != 0; 
    }

    template <typename TChar>
    bool_t String<TChar>::operator >(const String<TChar>& rhs) const
    {
        return compare(*this, rhs) > 0;
    }

    template <typename TChar>
    bool_t String<TChar>::operator <(const String<TChar>& rhs) const
    {
        return compare(*this, rhs) < 0;   
    }

    template <typename TChar>
    bool_t String<TChar>::operator >=(const String<TChar>& rhs) const
    {
        return compare(*this, rhs) >= 0;   
    }

    template <typename TChar>
    bool_t String<TChar>::operator <=(const String<TChar>& rhs) const
    {
        return compare(*this, rhs) <= 0;  
    }

    template <typename TChar>
    size_t String<TChar>::copy(TChar* buf) const
    {
        Memory::copy(Array<TChar>::ptr(), buf, sizeof(TChar) * Array<TChar>::count());
        buf[Array<TChar>::count()] = '\0';

        return Array<TChar>::count();
    }

    template <typename TChar>
    String<TChar>& String<TChar>::operator= (const String<TChar>& x)
    {
        Array<TChar>::init(x.ptr(), x.count());
        return *this;
    }

    template <typename TChar>
    String<TChar>& String<TChar>::operator= (TChar* x)
    {
        Array<TChar>::init(x, String<TChar>::strlen(x));
        return *this;
    }

    template <typename TChar>
    String<TChar>::operator const TChar*() const
    {
        return Array<TChar>::ptr();
    }
}
