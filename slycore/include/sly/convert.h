#pragma once

#include "sly/global.h"

namespace sly {

    //template<typename T>
    struct Convert {
    public:
        template<typename U, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
        static U parse(gsl::czstring<> str) {
            return (U)std::strtoull(str, nullptr, 10);
        }

        template<typename U, typename std::enable_if<std::is_floating_point<U>::value, float>::type = 0>
        static U parse(gsl::czstring<> str) {
             return (U)std::strtold(str, nullptr);
        }

        template<typename U, typename std::enable_if<std::is_enum<U>::value, int>::type = 0>
        static U parse(gsl::czstring<> str) {
            return Enum<U>::parse(str);
        }

        //template<typename T, typename std::enable_if<std::is_enum<T>::value, int>::type = 0>
        static gsl::czstring<> parse(gsl::czstring<> str) {
            return str;
        }
    };  
}