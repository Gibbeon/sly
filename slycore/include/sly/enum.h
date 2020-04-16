#pragma once

#include "sly/errors.h"
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
#define MAP31(m, x, ...) m(x) IDENTITY(MAP30(m, __VA_ARGS__))
#define MAP32(m, x, ...) m(x) IDENTITY(MAP31(m, __VA_ARGS__))
#define MAP33(m, x, ...) m(x) IDENTITY(MAP32(m, __VA_ARGS__))
#define MAP34(m, x, ...) m(x) IDENTITY(MAP33(m, __VA_ARGS__))
#define MAP35(m, x, ...) m(x) IDENTITY(MAP34(m, __VA_ARGS__))
#define MAP36(m, x, ...) m(x) IDENTITY(MAP35(m, __VA_ARGS__))
#define MAP37(m, x, ...) m(x) IDENTITY(MAP36(m, __VA_ARGS__))
#define MAP38(m, x, ...) m(x) IDENTITY(MAP37(m, __VA_ARGS__))
#define MAP39(m, x, ...) m(x) IDENTITY(MAP38(m, __VA_ARGS__))
#define MAP40(m, x, ...) m(x) IDENTITY(MAP39(m, __VA_ARGS__))
#define MAP41(m, x, ...) m(x) IDENTITY(MAP40(m, __VA_ARGS__))
#define MAP42(m, x, ...) m(x) IDENTITY(MAP41(m, __VA_ARGS__))
#define MAP43(m, x, ...) m(x) IDENTITY(MAP42(m, __VA_ARGS__))
#define MAP44(m, x, ...) m(x) IDENTITY(MAP43(m, __VA_ARGS__))
#define MAP45(m, x, ...) m(x) IDENTITY(MAP44(m, __VA_ARGS__))
#define MAP46(m, x, ...) m(x) IDENTITY(MAP45(m, __VA_ARGS__))
#define MAP47(m, x, ...) m(x) IDENTITY(MAP46(m, __VA_ARGS__))
#define MAP48(m, x, ...) m(x) IDENTITY(MAP47(m, __VA_ARGS__))
#define MAP49(m, x, ...) m(x) IDENTITY(MAP48(m, __VA_ARGS__))
#define MAP50(m, x, ...) m(x) IDENTITY(MAP49(m, __VA_ARGS__))
#define MAP51(m, x, ...) m(x) IDENTITY(MAP50(m, __VA_ARGS__))
#define MAP52(m, x, ...) m(x) IDENTITY(MAP51(m, __VA_ARGS__))
#define MAP53(m, x, ...) m(x) IDENTITY(MAP52(m, __VA_ARGS__))
#define MAP54(m, x, ...) m(x) IDENTITY(MAP53(m, __VA_ARGS__))
#define MAP55(m, x, ...) m(x) IDENTITY(MAP54(m, __VA_ARGS__))
#define MAP56(m, x, ...) m(x) IDENTITY(MAP55(m, __VA_ARGS__))
#define MAP57(m, x, ...) m(x) IDENTITY(MAP56(m, __VA_ARGS__))
#define MAP58(m, x, ...) m(x) IDENTITY(MAP57(m, __VA_ARGS__))
#define MAP59(m, x, ...) m(x) IDENTITY(MAP58(m, __VA_ARGS__))
#define MAP60(m, x, ...) m(x) IDENTITY(MAP59(m, __VA_ARGS__))
#define MAP61(m, x, ...) m(x) IDENTITY(MAP60(m, __VA_ARGS__))
#define MAP62(m, x, ...) m(x) IDENTITY(MAP61(m, __VA_ARGS__))
#define MAP63(m, x, ...) m(x) IDENTITY(MAP62(m, __VA_ARGS__))
#define MAP64(m, x, ...) m(x) IDENTITY(MAP63(m, __VA_ARGS__))
#define MAP65(m, x, ...) m(x) IDENTITY(MAP64(m, __VA_ARGS__))
#define MAP66(m, x, ...) m(x) IDENTITY(MAP65(m, __VA_ARGS__))
#define MAP67(m, x, ...) m(x) IDENTITY(MAP66(m, __VA_ARGS__))
#define MAP68(m, x, ...) m(x) IDENTITY(MAP67(m, __VA_ARGS__))
#define MAP69(m, x, ...) m(x) IDENTITY(MAP68(m, __VA_ARGS__))
#define MAP70(m, x, ...) m(x) IDENTITY(MAP69(m, __VA_ARGS__))
#define MAP71(m, x, ...) m(x) IDENTITY(MAP70(m, __VA_ARGS__))
#define MAP72(m, x, ...) m(x) IDENTITY(MAP71(m, __VA_ARGS__))
#define MAP73(m, x, ...) m(x) IDENTITY(MAP72(m, __VA_ARGS__))
#define MAP74(m, x, ...) m(x) IDENTITY(MAP73(m, __VA_ARGS__))
#define MAP75(m, x, ...) m(x) IDENTITY(MAP74(m, __VA_ARGS__))
#define MAP76(m, x, ...) m(x) IDENTITY(MAP75(m, __VA_ARGS__))
#define MAP77(m, x, ...) m(x) IDENTITY(MAP76(m, __VA_ARGS__))
#define MAP78(m, x, ...) m(x) IDENTITY(MAP77(m, __VA_ARGS__))
#define MAP79(m, x, ...) m(x) IDENTITY(MAP78(m, __VA_ARGS__))
#define MAP80(m, x, ...) m(x) IDENTITY(MAP79(m, __VA_ARGS__))
#define MAP81(m, x, ...) m(x) IDENTITY(MAP80(m, __VA_ARGS__))
#define MAP82(m, x, ...) m(x) IDENTITY(MAP81(m, __VA_ARGS__))
#define MAP83(m, x, ...) m(x) IDENTITY(MAP82(m, __VA_ARGS__))
#define MAP84(m, x, ...) m(x) IDENTITY(MAP83(m, __VA_ARGS__))
#define MAP85(m, x, ...) m(x) IDENTITY(MAP84(m, __VA_ARGS__))
#define MAP86(m, x, ...) m(x) IDENTITY(MAP85(m, __VA_ARGS__))
#define MAP87(m, x, ...) m(x) IDENTITY(MAP86(m, __VA_ARGS__))
#define MAP88(m, x, ...) m(x) IDENTITY(MAP87(m, __VA_ARGS__))
#define MAP89(m, x, ...) m(x) IDENTITY(MAP88(m, __VA_ARGS__))
#define MAP90(m, x, ...) m(x) IDENTITY(MAP89(m, __VA_ARGS__))
#define MAP91(m, x, ...) m(x) IDENTITY(MAP90(m, __VA_ARGS__))
#define MAP92(m, x, ...) m(x) IDENTITY(MAP91(m, __VA_ARGS__))
#define MAP93(m, x, ...) m(x) IDENTITY(MAP92(m, __VA_ARGS__))
#define MAP94(m, x, ...) m(x) IDENTITY(MAP93(m, __VA_ARGS__))
#define MAP95(m, x, ...) m(x) IDENTITY(MAP94(m, __VA_ARGS__))
#define MAP96(m, x, ...) m(x) IDENTITY(MAP95(m, __VA_ARGS__))
#define MAP97(m, x, ...) m(x) IDENTITY(MAP96(m, __VA_ARGS__))
#define MAP98(m, x, ...) m(x) IDENTITY(MAP97(m, __VA_ARGS__))
#define MAP99(m, x, ...) m(x) IDENTITY(MAP98(m, __VA_ARGS__))
#define MAP100(m, x, ...) m(x) IDENTITY(MAP99(m, __VA_ARGS__))
#define MAP101(m, x, ...) m(x) IDENTITY(MAP100(m, __VA_ARGS__))
#define MAP102(m, x, ...) m(x) IDENTITY(MAP101(m, __VA_ARGS__))
#define MAP103(m, x, ...) m(x) IDENTITY(MAP102(m, __VA_ARGS__))
#define MAP104(m, x, ...) m(x) IDENTITY(MAP103(m, __VA_ARGS__))
#define MAP105(m, x, ...) m(x) IDENTITY(MAP104(m, __VA_ARGS__))
#define MAP106(m, x, ...) m(x) IDENTITY(MAP105(m, __VA_ARGS__))
#define MAP107(m, x, ...) m(x) IDENTITY(MAP106(m, __VA_ARGS__))
#define MAP108(m, x, ...) m(x) IDENTITY(MAP107(m, __VA_ARGS__))
#define MAP109(m, x, ...) m(x) IDENTITY(MAP108(m, __VA_ARGS__))
#define MAP110(m, x, ...) m(x) IDENTITY(MAP109(m, __VA_ARGS__))
#define MAP111(m, x, ...) m(x) IDENTITY(MAP110(m, __VA_ARGS__))
#define MAP112(m, x, ...) m(x) IDENTITY(MAP111(m, __VA_ARGS__))
#define MAP113(m, x, ...) m(x) IDENTITY(MAP112(m, __VA_ARGS__))
#define MAP114(m, x, ...) m(x) IDENTITY(MAP113(m, __VA_ARGS__))
#define MAP115(m, x, ...) m(x) IDENTITY(MAP114(m, __VA_ARGS__))
#define MAP116(m, x, ...) m(x) IDENTITY(MAP115(m, __VA_ARGS__))
#define MAP117(m, x, ...) m(x) IDENTITY(MAP116(m, __VA_ARGS__))
#define MAP118(m, x, ...) m(x) IDENTITY(MAP117(m, __VA_ARGS__))
#define MAP119(m, x, ...) m(x) IDENTITY(MAP118(m, __VA_ARGS__))
#define MAP120(m, x, ...) m(x) IDENTITY(MAP119(m, __VA_ARGS__))

#define EVALUATE_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, count, ...) count

#define COUNT(...) \
    IDENTITY(EVALUATE_COUNT(__VA_ARGS__, 120,	119,	118,	117,	116,	115,	114,	113,	112,	111,	110,	109,	108,	107,	106,	105,	104,	103,	102,	101,	100,	99,	98,	97,	96,	95,	94,	93,	92,	91,	90,	89,	88,	87,	86,	85,	84,	83,	82,	81,	80,	79,	78,	77,	76,	75,	74,	73,	72,	71,	70,	69,	68,	67,	66,	65,	64,	63,	62,	61,	60,	59,	58,	57,	56,	55,	54,	53,	52,	51,	50,	49,	48,	47,	46,	45,	44,	43,	42,	41,	40,	39,	38,	37,	36,	35,	34,	33,	32,	31,	30,	29,	28,	27,	26,	25,	24,	23,	22,	21,	20,	19,	18,	17,	16,	15,	14,	13,	12,	11,	10,	9,	8,	7,	6,	5,	4,	3,	2,	1))

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

            static retval<const char_t*> toString(T value);                
            static retval<const T> parse(const char_t* name);                                                              

            template<size_t N, size_t NSize>
            static retval<bool_t> init(size_t count, const char_t* const (&raw_names)[N], const s32 (&values)[N]);

            static size_t count();
            static gsl::span<s32> values();
            static gsl::span<u32> hashes();
            static gsl::span<char_t*> names();

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
    gsl::span<s32> Enum<T>::values() {
        return gsl::make_span(_values, _count );
    }
        
    template<typename T>
    gsl::span<u32> Enum<T>::hashes() {
        return gsl::make_span(_hashes, _count );
    }

    template<typename T>
    gsl::span<char_t*> Enum<T>::names() {
        return gsl::make_span(_names, _count );
    }

    template<typename T>
    retval<const TypeInfo&> getType() {
        static const TypeInfo instance = TypeInfo::get<T>();
        return reference(instance);
    }
    
    template<typename T>
    retval<const char_t*> Enum<T>::toString(T value)              
    {                                                                  
        for (size_t index = 0; index < count(); ++index) {             
            if (values()[index] == value)                             
                return names()[index];                                 
        }                                      

        static const StatusCode SLY_NOTFOUND = 0x02;                        
                                                                    
        return failed<const char_t*>( (StatusCode)SLY_NOTFOUND, "The value could not be parsed into an Enum name" );                                                   
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

#define ENUM_DECL_OFTYPE(EnumName, Type, ...)                          \
typedef enum : Type {                                                  \
    __VA_ARGS__                                                        \
} EnumName;                                                            \
                                                                       \
namespace { bool_t EnumName ## _initialized = ::sly::Enum<EnumName>::init<IDENTITY(COUNT(__VA_ARGS__)),STRING_LEN(__VA_ARGS__)>( IDENTITY(COUNT(__VA_ARGS__)) , { IDENTITY(STRINGIZE(__VA_ARGS__)) }, { IDENTITY(IGNORE_ASSIGN(__VA_ARGS__)) });  }                                                                 

