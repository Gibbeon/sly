#pragma once

#define TOSTRING(x) #x
#define STRINGIFY(x) TOSTRING(x)
#define FILE_LINE __FILE__ ":" STRINGIFY(__LINE__)
#define NOOP() (void(0))

#define THROW(message)  throw Exception(__LINE__, __FILE__, message)


template< unsigned int value_ > struct static_log2
{
    static const unsigned int result = static_log2< value_ / 2 >::result + 1 ;
};

template<> struct static_log2< 1 > { static const unsigned int result = 0 ; } ;
template<> struct static_log2< 0 > { } ;

template< const char char_, const char* str_, unsigned int value_ = 0 > struct static_strlen
{
    static const unsigned int result = static_strlen<str_[value_], str_, value_ + 1>::result;
};

template<const char* str_, unsigned int value_> struct static_strlen< '\0', str_, value_ > { static const unsigned int result = value_ ; } ;

// Generate CRC lookup table
template <unsigned c, int k = 8>
struct f : f<((c & 1) ? 0xedb88320 : 0) ^ (c >> 1), k - 1> {};
template <unsigned c> struct f<c, 0>{enum {value = c};};

