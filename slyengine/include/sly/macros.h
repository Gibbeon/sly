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
