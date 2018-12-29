#pragma once

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned char ubyte;
typedef signed char sbyte;

typedef float single;
typedef long double triple;

typedef bool bool_t;
typedef double real_t;
typedef char char_t;
typedef const char_t* string_t;

typedef s32 int_t;
typedef s64 long_t;
typedef u32 uint_t;
typedef u64 ulong_t;

typedef u64 size_t;

typedef void* ptr_t;

#ifdef FALSE
#undef FALSE
#endif
#define FALSE false
#ifdef TRUE
#undef TRUE
#endif
#define TRUE true

#include "sly/ref.h"
#include "sly/out_ptr.h"
#include "sly/local_ptr.h"
#include "sly/string.h"
#include "sly/pair.h"
#include "sly/exception.h"
#include "sly/function.h"
