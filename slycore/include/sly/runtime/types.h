#pragma once

#define TYPE_INFO_TYPENAME(typename) TOSTRING(typename)
#define TYPE_INFO_IID(typename) IID_ ## typename
#define TYPE_INFO(typename) virtual TypeInfo getTypeInfo() { return TypeInfo(TYPE_INFO_TYPENAME(typename), TYPE_INFO_IID(typename) ); }

namespace sly {
    typedef enum {
        IID_Void,
        IID_U8,
        IID_U16,
        IID_U32,
        IID_U64,
        IID_F32,
        IID_F64,
        IID_F80,
        IID_Char,
        IID_WChar,
        IID_String,
        IID_Vector,
        IID_Map,
        IID_Array,
        TYPE_INFO_IID(MemoryManager),
    } IID_TypeNames;
}