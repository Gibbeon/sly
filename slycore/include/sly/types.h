#pragma once

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef float f64;
typedef long double f80;

typedef bool bool_t;
typedef f32 real_t;
typedef u8 char_t;
typedef u8 byte_t;
typedef s16 short_t;
typedef s32 int_t;
typedef s64 long_t;
typedef u32 ushort_t;
typedef u32 uint_t;
typedef u64 ulong_t;
typedef u64 size_t;
typedef void* vptr_t;

#ifdef FALSE
#undef FALSE
#endif
#ifdef TRUE
#undef TRUE
#endif
#ifdef NULL
#undef NULL
#endif 

#define FALSE false
#define TRUE true
#define NULL nullptr