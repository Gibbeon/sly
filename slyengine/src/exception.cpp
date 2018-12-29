#include "sly/exception.h"

using namespace sly;

Exception::Exception(s32 line, String<> file) :
    line_(line),
    file_(file)
{
    
}

Exception::Exception(s32 line, String<> file, String<> message) :
    line_(line),
    file_(file),
    message_(message)
{
    
}

Exception::Exception(s32 line, String<> file, String<> message, const Exception& inner) :
    line_(line),
    file_(file),
    message_(message),
    inner_(&inner)

{
    
}

Exception::Exception(const Exception& copy) :
    line_(copy.line_),
    file_(copy.file_),
    message_(copy.message_),
    inner_(copy.inner_)
{

}

const String<>& Exception::message() const
{
    return message_;
}

s32 Exception::line() const
{
    return line_;
}

const String<>& Exception::file() const
{
    return file_;
}

const Exception* Exception::inner() const
{
    return inner_;
}
