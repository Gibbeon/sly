#pragma once

#include "sly/global.h"
#include "sly/runtime/typeinfo.h"

#include <cstddef>
#include <string>

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        // this needs to be global
        #define __iscsym(_c) (isalnum(_c) || ((_c)=='_'))

        // Extra functions for MinGW. Most of these are the _s functions which are in
        // the Microsoft Visual Studio C++ CRT.
        #define _TRUNCATE 0
        #define STRUNCATE 80

        extern int strncpy_s(char* dest, size_t dest_size, const char* source, size_t count);
        
    #endif
#endif 




#define MAP(macro, ...) \
    IDENTITY( \
        APPLY(CHOOSE_MAP_START, COUNT(__VA_ARGS__)) \
            (macro, __VA_ARGS__))

#define CHOOSE_MAP_START(count) MAP ## count

#define APPLY(macro, ...) IDENTITY(macro(__VA_ARGS__))

// Needed to expand __VA_ARGS__ "eagerly" on the MSVC preprocessor.
#define IDENTITY(x) x

#define MAP1(m, x)      m(x)
#define MAP2(m, x, ...) m(x) IDENTITY(MAP1(m, __VA_ARGS__))
#define MAP3(m, x, ...) m(x) IDENTITY(MAP2(m, __VA_ARGS__))
#define MAP4(m, x, ...) m(x) IDENTITY(MAP3(m, __VA_ARGS__))
#define MAP5(m, x, ...) m(x) IDENTITY(MAP4(m, __VA_ARGS__))
#define MAP6(m, x, ...) m(x) IDENTITY(MAP5(m, __VA_ARGS__))
#define MAP7(m, x, ...) m(x) IDENTITY(MAP6(m, __VA_ARGS__))
#define MAP8(m, x, ...) m(x) IDENTITY(MAP7(m, __VA_ARGS__))
#define MAP9(m, x, ...) m(x) IDENTITY(MAP8(m, __VA_ARGS__))
#define MAP10(m, x, ...) m(x) IDENTITY(MAP9(m, __VA_ARGS__))
#define MAP11(m, x, ...) m(x) IDENTITY(MAP10(m, __VA_ARGS__))
#define MAP12(m, x, ...) m(x) IDENTITY(MAP11(m, __VA_ARGS__))
#define MAP13(m, x, ...) m(x) IDENTITY(MAP12(m, __VA_ARGS__))
#define MAP14(m, x, ...) m(x) IDENTITY(MAP13(m, __VA_ARGS__))
#define MAP15(m, x, ...) m(x) IDENTITY(MAP14(m, __VA_ARGS__))
#define MAP16(m, x, ...) m(x) IDENTITY(MAP15(m, __VA_ARGS__))
#define MAP17(m, x, ...) m(x) IDENTITY(MAP16(m, __VA_ARGS__))
#define MAP18(m, x, ...) m(x) IDENTITY(MAP17(m, __VA_ARGS__))
#define MAP19(m, x, ...) m(x) IDENTITY(MAP18(m, __VA_ARGS__))
#define MAP20(m, x, ...) m(x) IDENTITY(MAP19(m, __VA_ARGS__))
#define MAP21(m, x, ...) m(x) IDENTITY(MAP20(m, __VA_ARGS__))
#define MAP22(m, x, ...) m(x) IDENTITY(MAP21(m, __VA_ARGS__))
#define MAP23(m, x, ...) m(x) IDENTITY(MAP22(m, __VA_ARGS__))
#define MAP24(m, x, ...) m(x) IDENTITY(MAP23(m, __VA_ARGS__))
#define MAP25(m, x, ...) m(x) IDENTITY(MAP24(m, __VA_ARGS__))
#define MAP26(m, x, ...) m(x) IDENTITY(MAP25(m, __VA_ARGS__))
#define MAP27(m, x, ...) m(x) IDENTITY(MAP26(m, __VA_ARGS__))
#define MAP28(m, x, ...) m(x) IDENTITY(MAP27(m, __VA_ARGS__))
#define MAP29(m, x, ...) m(x) IDENTITY(MAP28(m, __VA_ARGS__))
#define MAP30(m, x, ...) m(x) IDENTITY(MAP29(m, __VA_ARGS__))

#define EVALUATE_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, count, ...) count

#define COUNT(...) \
    IDENTITY(EVALUATE_COUNT(__VA_ARGS__, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#define STRING_LEN(...) sizeof( #__VA_ARGS__ )

struct ignore_assign {
    ignore_assign(int value) : _value(value) { }
    operator int() const { return _value; }

    const ignore_assign& operator =(int dummy) { return *this; }

    int _value;
};

#define IGNORE_ASSIGN_SINGLE(expression) (ignore_assign)expression,
#define IGNORE_ASSIGN(...) IDENTITY(MAP(IGNORE_ASSIGN_SINGLE, __VA_ARGS__))

#define STRINGIZE_SINGLE(expression) #expression,
#define STRINGIZE(...) IDENTITY(MAP(STRINGIZE_SINGLE, __VA_ARGS__))

static char_t* ltrim(char_t* str) {
    while (*str && isspace(*str++)) {}
    return str;
}

static char_t* rtrim(char_t* str) {
    char_t* buffer = str;
    while (*str++); // move to end of string
    size_t end = str - buffer - 1; 
    while (end > 0 && isspace(buffer[end - 1])) --end; // backup over trailing spaces
    buffer[end] = 0; // remove trailing spaces
    return str;
}

static char_t* trim(char_t* str) {
    return ltrim(rtrim(str));
}

namespace sly {

    template<typename T>
    struct Enum 
    {
        public:
            using underlying_type = __underlying_type(T);
            using type = T;

            static retval<const TypeInfo&> getType();

            static retval<const char_t* const> toString(T value);                
            static retval<const T> parse(const char_t* name);                                                              

            template<size_t N, size_t NSize>
            static retval<bool_t> init(size_t count, const char_t* const (&raw_names)[N], const s32 (&values)[N]);

            static size_t count();
            static gsl::span<const s32*> values();
            static gsl::span<const u32*> hashes();
            static gsl::span<const char_t* const*> names();

        protected:
            static size_t _count;
            static s32* _values;
            static u32* _hashes;
            static char_t** _names;
    };

    template<typename T>
    size_t Enum<T>::count() {
        return _count;
    }
       
    template<typename T>
    gsl::span<const s32*> Enum<T>::values() {
        return gsl::make_span(_values, _count );
    }
        
    template<typename T>
    gsl::span<const u32*> Enum<T>::hashes() {
        return gsl::make_span(_hashes, _count );
    }

    template<typename T>
    gsl::span<const char_t* const*> Enum<T>::names() {
        return gsl::make_span(_names, _count );
    }

    template<typename T>
    retval<const TypeInfo&> getType() {
        static const TypeInfo instance = TypeInfo::get<T>();
        return return_reference(instance);
    }
    
    template<typename T>
    retval<const char_t* const> Enum<T>::toString(T value)              
    {                                                                  
        for (size_t index = 0; index < count(); ++index) {             
            if (values()[index] == value)                             
                return names()[index];                                 
        }                                                              
                                                                    
        return return_error( SLY_NOTFOUND );                                                   
    }                                                                  
                
    template<typename T>                                                          
    retval<const T> Enum<T>::parse(const char_t* name)                    
    {                                                                  
        bool_t started = false;                                        
        size_t start_pos = 0;                                          
        size_t str_len = strlen(name);                                 
        u32 result = 0;                                                
                                                                    
        for(size_t n = 0; n < str_len + 1; n++) {                      
            constexpr const char_t delims[] = ",|\t\n\v\f\r ";         
                                                                    
            if(started == false) {                                     
                started = __iscsym(name[n]);                           
                if(started) {                                          
                    start_pos = n;                                     
                }                                                      
            } else {                                                   
                if(!(started = __iscsym(name[n]))) {                   
                    u32 hash = dynamic_crc32_n(&(name[start_pos]),     
                        n - start_pos);                                
                    for (size_t index = 0; index < count(); ++index) { 
                        if (hashes()[index] == hash) {                 
                            result |= values()[index]; }  }            
                }                                                      
            }                                                          
        }                                                              
        return (T)result;                                       
    }    
    
    template<size_t N>
    static constexpr size_t sizeof_r(const char_t* const (&raw_names)[N], size_t index = N) {
        index--;
        return strlen(raw_names[index]) + sizeof_r(raw_names, index);
    }

    template<typename T>
    template<size_t N, size_t NSize>
    retval<bool_t> Enum<T>::init(size_t count, const char_t* const (&raw_names)[N], const s32 (&values)[N]) {

        static char_t*  nameary_buffer[ N ];
        static char_t   names_buffer[ ( NSize + 1) ];
        static u32      hashes_buffer[ N ];
        static s32      values_buffer[ N ];
        static bool_t   initialized = false;

        if(!initialized) {        
            char_t* ptr_names = names_buffer;

            _names = nameary_buffer;  
            _hashes = hashes_buffer;    
            _values = values_buffer;
            _count = count;

            for (size_t index = 0; index < _count; ++index) {  
                _values[index] = values[index];       
                size_t length =  std::strcspn(raw_names[index], " =\t\n\r") + 1;    
                
                _names[index] = ptr_names;
                ptr_names += (length + 1);         
                                                                        
                ::strncpy_s(_names[index], length, raw_names[index], _TRUNCATE);                      
                                                                
                _names[index][length] = '\0';                 
                                                                        
                _hashes[index] = dynamic_crc32(_names[index]);      
            }     
            initialized = true;  
            return true;
        }
        return true;
    }

    template<typename T>
    size_t Enum<T>::_count;

    template<typename T>
    s32* Enum<T>::_values;

    template<typename T>
    u32* Enum<T>::_hashes;

    template<typename T>
    char_t** Enum<T>::_names;
}

#define ENUM_DECL(EnumName, ...)                                       \
typedef enum  {                                                        \
    __VA_ARGS__                                                        \
} EnumName;                                                            \
                                                                       \
namespace { bool_t EnumName ## _initialized = ::sly::Enum<EnumName>::init<IDENTITY(COUNT(__VA_ARGS__)),STRING_LEN(__VA_ARGS__)>( IDENTITY(COUNT(__VA_ARGS__)) , { IDENTITY(STRINGIZE(__VA_ARGS__)) }, { IDENTITY(IGNORE_ASSIGN(__VA_ARGS__)) });  }                                                                 
