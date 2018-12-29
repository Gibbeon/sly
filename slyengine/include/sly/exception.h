#pragma once


#include "sly/global.h"
#include "sly/string.h"

namespace sly {
    class Exception
    {
        public:
            Exception(s32 line, String<> file);
            Exception(s32 line, String<> file, String<> message);
            Exception(s32 line, String<> file, String<> message, const Exception& inner);
            Exception(const Exception& copy);

            s32 line() const;
            const String<>& message() const;
            const String<>& file() const;
            const Exception* inner() const;

        private:
            s32 line_;
            String<> file_;
            String<> message_;
            const Exception* inner_;
    };
}