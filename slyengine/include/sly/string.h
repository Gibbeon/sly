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
            String(const TChar* data, s32 length);
            String(const String<TChar>& copy);

            String<TChar> substring(s32 offset, s32 length) const;

            bool_t operator ==(const String<TChar> &rhs) const;
            bool_t operator !=(const String<TChar> &rhs) const;
            bool_t operator >(const String<TChar> &rhs) const;
            bool_t operator <(const String<TChar> &rhs) const;
            bool_t operator >=(const String<TChar> &rhs) const;
            bool_t operator <=(const String<TChar> &rhs) const;

            String& operator= (const String<TChar>& x);
            String& operator= (TChar* x);

            explicit operator const TChar*() const;
            
            s32 copy(TChar* buf) const;

            static s32 strlen(const TChar* str);
            static s32 copy(const String<TChar>& src, String<TChar>& dest);
            static s32 compare(const String<TChar>& lhs, const String<TChar>& rhs);
        private:
            
    };

    #include "sly/string.hpp"
}
