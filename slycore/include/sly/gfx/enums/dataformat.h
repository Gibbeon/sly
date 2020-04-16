#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(eDataFormat,
            eDataFormat_Unknown,
            eDataFormat_R32G32B32A32_TYPELESS,
            eDataFormat_R32G32B32A32_FLOAT,
            eDataFormat_R32G32B32A32_UINT,
            eDataFormat_R32G32B32A32_SINT,
            eDataFormat_R32G32B32_TYPELESS,
            eDataFormat_R32G32B32_FLOAT,
            eDataFormat_R32G32B32_UINT,
            eDataFormat_R32G32B32_SINT,
            eDataFormat_R16G16B16A16_TYPELESS,
            eDataFormat_R16G16B16A16_FLOAT,
            eDataFormat_R16G16B16A16_UNORM,
            eDataFormat_R16G16B16A16_UINT,
            eDataFormat_R16G16B16A16_SNORM,
            eDataFormat_R16G16B16A16_SINT,
            eDataFormat_R32G32_TYPELESS,
            eDataFormat_R32G32_FLOAT,
            eDataFormat_R32G32_UINT,
            eDataFormat_R32G32_SINT,
            eDataFormat_R32G8X24_TYPELESS,
            eDataFormat_D32_FLOAT_S8X24_UINT,
            eDataFormat_R32_FLOAT_X8X24_TYPELESS,
            eDataFormat_X32_TYPELESS_G8X24_UINT,
            eDataFormat_R10G10B10A2_TYPELESS,
            eDataFormat_R10G10B10A2_UNORM,
            eDataFormat_R10G10B10A2_UINT,
            eDataFormat_R11G11B10_FLOAT,
            eDataFormat_R8G8B8A8_TYPELESS,
            eDataFormat_R8G8B8A8_UNORM,
            eDataFormat_R8G8B8A8_UNORM_SRGB,
            eDataFormat_R8G8B8A8_UINT,
            eDataFormat_R8G8B8A8_SNORM,
            eDataFormat_R8G8B8A8_SINT,
            eDataFormat_R16G16_TYPELESS,
            eDataFormat_R16G16_FLOAT,
            eDataFormat_R16G16_UNORM,
            eDataFormat_R16G16_UINT,
            eDataFormat_R16G16_SNORM,
            eDataFormat_R16G16_SINT,
            eDataFormat_R32_TYPELESS,
            eDataFormat_D32_FLOAT,
            eDataFormat_R32_FLOAT,
            eDataFormat_R32_UINT,
            eDataFormat_R32_SINT,
            eDataFormat_R24G8_TYPELESS,
            eDataFormat_D24_UNORM_S8_UINT,
            eDataFormat_R24_UNORM_X8_TYPELESS,
            eDataFormat_X24_TYPELESS_G8_UINT,
            eDataFormat_R8G8_TYPELESS,
            eDataFormat_R8G8_UNORM,
            eDataFormat_R8G8_UINT,
            eDataFormat_R8G8_SNORM,
            eDataFormat_R8G8_SINT,
            eDataFormat_R16_TYPELESS,
            eDataFormat_R16_FLOAT,
            eDataFormat_D16_UNORM,
            eDataFormat_R16_UNORM,
            eDataFormat_R16_UINT,
            eDataFormat_R16_SNORM,
            eDataFormat_R16_SINT,
            eDataFormat_R8_TYPELESS,
            eDataFormat_R8_UNORM,
            eDataFormat_R8_UINT,
            eDataFormat_R8_SNORM,
            eDataFormat_R8_SINT,
            eDataFormat_A8_UNORM,
            eDataFormat_R1_UNORM,
            eDataFormat_R9G9B9E5_SHAREDEXP,
            eDataFormat_R8G8_B8G8_UNORM,
            eDataFormat_G8R8_G8B8_UNORM,
            eDataFormat_BC1_TYPELESS,
            eDataFormat_BC1_UNORM,
            eDataFormat_BC1_UNORM_SRGB,
            eDataFormat_BC2_TYPELESS,
            eDataFormat_BC2_UNORM,
            eDataFormat_BC2_UNORM_SRGB,
            eDataFormat_BC3_TYPELESS,
            eDataFormat_BC3_UNORM,
            eDataFormat_BC3_UNORM_SRGB,
            eDataFormat_BC4_TYPELESS,
            eDataFormat_BC4_UNORM,
            eDataFormat_BC4_SNORM,
            eDataFormat_BC5_TYPELESS,
            eDataFormat_BC5_UNORM,
            eDataFormat_BC5_SNORM,
            eDataFormat_B5G6R5_UNORM,
            eDataFormat_B5G5R5A1_UNORM,
            eDataFormat_B8G8R8A8_UNORM,
            eDataFormat_B8G8R8X8_UNORM,
            eDataFormat_R10G10B10_XR_BIAS_A2_UNORM,
            eDataFormat_B8G8R8A8_TYPELESS,
            eDataFormat_B8G8R8A8_UNORM_SRGB,
            eDataFormat_B8G8R8X8_TYPELESS,
            eDataFormat_B8G8R8X8_UNORM_SRGB,
            eDataFormat_BC6H_TYPELESS,
            eDataFormat_BC6H_UF16,
            eDataFormat_BC6H_SF16,
            eDataFormat_BC7_TYPELESS,
            eDataFormat_BC7_UNORM,
            eDataFormat_BC7_UNORM_SRGB,
            eDataFormat_Size,
            eDataFormat_Default = eDataFormat_R8G8B8A8_UNORM
         ); 


        ENUM_DECL(eVideoDataFormat,
            eVideoDataFormat_AYUV,
            eVideoDataFormat_Y410,
            eVideoDataFormat_Y416,
            eVideoDataFormat_NV12,
            eVideoDataFormat_P010,
            eVideoDataFormat_P016,
            eVideoDataFormat_420_OPAQUE,
            eVideoDataFormat_YUY2,
            eVideoDataFormat_Y210,
            eVideoDataFormat_Y216,
            eVideoDataFormat_NV11,
            eVideoDataFormat_AI44,
            eVideoDataFormat_IA44,
            eVideoDataFormat_P8,
            eVideoDataFormat_A8P8,
            eVideoDataFormat_B4G4R4A4_UNORM,
            eVideoDataFormat_P208,
            eVideoDataFormat_V208,
            eVideoDataFormat_V408,
            eVideoDataFormat_Size,
            eVideoDataFormat_Default = eVideoDataFormat_AYUV
        );


        static size_t sizeOf(eDataFormat format) {
            switch (format) {
                case  eDataFormat_R32G32B32A32_TYPELESS:
                case  eDataFormat_R32G32B32A32_FLOAT:
                case  eDataFormat_R32G32B32A32_UINT:
                case  eDataFormat_R32G32B32A32_SINT:
                    return sizeof(u32) * 4;
                case  eDataFormat_R32G32B32_TYPELESS:
                case  eDataFormat_R32G32B32_FLOAT:
                case  eDataFormat_R32G32B32_UINT:
                case  eDataFormat_R32G32B32_SINT:
                    return sizeof(u32) * 3;
                case  eDataFormat_R16G16B16A16_TYPELESS:
                case  eDataFormat_R16G16B16A16_FLOAT:
                case  eDataFormat_R16G16B16A16_UNORM:
                case  eDataFormat_R16G16B16A16_UINT:
                case  eDataFormat_R16G16B16A16_SNORM:
                case  eDataFormat_R16G16B16A16_SINT:
                    return sizeof(u16) * 3;
                case  eDataFormat_R32G32_TYPELESS:
                case  eDataFormat_R32G32_FLOAT:
                case  eDataFormat_R32G32_UINT:
                case  eDataFormat_R32G32_SINT:
                case eDataFormat_R32G8X24_TYPELESS:
                case eDataFormat_D32_FLOAT_S8X24_UINT:
                case eDataFormat_R32_FLOAT_X8X24_TYPELESS:
                case eDataFormat_X32_TYPELESS_G8X24_UINT:
                case eDataFormat_R10G10B10A2_TYPELESS:
                case eDataFormat_R10G10B10A2_UNORM:
                case eDataFormat_R10G10B10A2_UINT:
                case eDataFormat_R11G11B10_FLOAT:                
                    return sizeof(u32) * 2;
                case eDataFormat_R8G8B8A8_TYPELESS:
                case eDataFormat_R8G8B8A8_UNORM:
                case eDataFormat_R8G8B8A8_UNORM_SRGB:
                case eDataFormat_R8G8B8A8_UINT:
                case eDataFormat_R8G8B8A8_SNORM:
                case eDataFormat_R8G8B8A8_SINT:                
                    return sizeof(u8) * 4;
                case eDataFormat_R16G16_TYPELESS:
                case eDataFormat_R16G16_FLOAT:
                case eDataFormat_R16G16_UNORM:
                case eDataFormat_R16G16_UINT:
                case eDataFormat_R16G16_SNORM:
                case eDataFormat_R16G16_SINT:                
                    return sizeof(u16) * 2;
                case eDataFormat_R32_TYPELESS:
                case eDataFormat_D32_FLOAT:
                case eDataFormat_R32_FLOAT:
                case eDataFormat_R32_UINT:
                case eDataFormat_R32_SINT:
                case eDataFormat_R24G8_TYPELESS:
                case eDataFormat_D24_UNORM_S8_UINT:
                case eDataFormat_R24_UNORM_X8_TYPELESS:
                case eDataFormat_X24_TYPELESS_G8_UINT:
                    return sizeof(u32);
                case eDataFormat_R8G8_TYPELESS:
                case eDataFormat_R8G8_UNORM:
                case eDataFormat_R8G8_UINT:
                case eDataFormat_R8G8_SNORM:
                case eDataFormat_R8G8_SINT:
                case eDataFormat_R16_TYPELESS:
                case eDataFormat_R16_FLOAT:
                case eDataFormat_D16_UNORM:
                case eDataFormat_R16_UNORM:
                case eDataFormat_R16_UINT:
                case eDataFormat_R16_SNORM:
                case eDataFormat_R16_SINT:                
                    return sizeof(u16);
                case eDataFormat_R8_TYPELESS:
                case eDataFormat_R8_UNORM:
                case eDataFormat_R8_UINT:
                case eDataFormat_R8_SNORM:
                case eDataFormat_R8_SINT:
                case eDataFormat_A8_UNORM:                               
                    return sizeof(u8);
                case eDataFormat_R1_UNORM:
                case eDataFormat_R9G9B9E5_SHAREDEXP:
                case eDataFormat_R8G8_B8G8_UNORM:
                case eDataFormat_G8R8_G8B8_UNORM:
                case eDataFormat_BC1_TYPELESS:
                case eDataFormat_BC1_UNORM:
                case eDataFormat_BC1_UNORM_SRGB:
                case eDataFormat_BC2_TYPELESS:
                case eDataFormat_BC2_UNORM:
                case eDataFormat_BC2_UNORM_SRGB:
                case eDataFormat_BC3_TYPELESS:
                case eDataFormat_BC3_UNORM:
                case eDataFormat_BC3_UNORM_SRGB:
                case eDataFormat_BC4_TYPELESS:
                case eDataFormat_BC4_UNORM:
                case eDataFormat_BC4_SNORM:
                case eDataFormat_BC5_TYPELESS:
                case eDataFormat_BC5_UNORM:
                case eDataFormat_BC5_SNORM:
                case eDataFormat_B5G6R5_UNORM:
                case eDataFormat_B5G5R5A1_UNORM:
                case eDataFormat_B8G8R8A8_UNORM:
                case eDataFormat_B8G8R8X8_UNORM:
                case eDataFormat_R10G10B10_XR_BIAS_A2_UNORM:
                case eDataFormat_B8G8R8A8_TYPELESS:
                case eDataFormat_B8G8R8A8_UNORM_SRGB:
                case eDataFormat_B8G8R8X8_TYPELESS:
                case eDataFormat_B8G8R8X8_UNORM_SRGB:
                case eDataFormat_BC6H_TYPELESS:
                case eDataFormat_BC6H_UF16:
                case eDataFormat_BC6H_SF16:
                case eDataFormat_BC7_TYPELESS:
                case eDataFormat_BC7_UNORM:
                case eDataFormat_BC7_UNORM_SRGB:
                    return sizeof(u32);

                Ensures(0);
            }
        }
    }
}

