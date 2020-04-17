#pragma once

#include "sly/d3d12.h"
#include "sly/gfx.h"
#include "sly/d3d12/gfx/shader.h"

template<typename TFrom, typename TTo>
struct EnumConvert {};

#define ENUM_MAP_DECL_BEGIN(eTypeFrom, eTypeTo)     template<> struct EnumConvert<eTypeFrom, eTypeTo> { static eTypeTo convert(eTypeFrom value) { switch(value) {
#define ENUM_MAP(from, to)                          case from: return to;
#define ENUM_MAP_DECL_END(eTypeFrom, eTypeTo)       } return (eTypeTo)-1; }};


template<typename TTo, typename TFrom>
constexpr TTo enum_convert_to(TFrom src) {
    return EnumConvert<TFrom, TTo>::convert(src);
}

template<typename TTo, typename TFrom>
constexpr TTo enum_convert_assign(TFrom src, TTo& dest) {
    return dest = EnumConvert<TFrom, TTo>::convert(src);
}

#define D3D_DECL_CAST(TTo, TFrom, ...)                                  \
 struct TTo ## _CAST : public TTo { TTo ## _CAST(const TFrom& src) {          \
    __VA_ARGS__                                                         \
} }; inline TTo& D3DAssign(TTo& dest, const TFrom& src) { return dest = TTo ## _CAST(src); } inline TTo D3DConvert(const TFrom& src) { return TTo ## _CAST(src); }

namespace sly {
    namespace gfx {
        ENUM_MAP_DECL_BEGIN(eDataFormat, DXGI_FORMAT) {
            ENUM_MAP(eDataFormat_Unknown, DXGI_FORMAT_UNKNOWN);
            ENUM_MAP(eDataFormat_R32G32B32A32_TYPELESS, DXGI_FORMAT_R32G32B32A32_TYPELESS);
            ENUM_MAP(eDataFormat_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT);
            ENUM_MAP(eDataFormat_R32G32B32A32_UINT, DXGI_FORMAT_R32G32B32A32_UINT);
            ENUM_MAP(eDataFormat_R32G32B32A32_SINT, DXGI_FORMAT_R32G32B32A32_SINT);
            ENUM_MAP(eDataFormat_R32G32B32_TYPELESS, DXGI_FORMAT_R32G32B32_TYPELESS);
            ENUM_MAP(eDataFormat_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT);
            ENUM_MAP(eDataFormat_R32G32B32_UINT, DXGI_FORMAT_R32G32B32_UINT);
            ENUM_MAP(eDataFormat_R32G32B32_SINT, DXGI_FORMAT_R32G32B32_SINT);
            ENUM_MAP(eDataFormat_R16G16B16A16_TYPELESS, DXGI_FORMAT_R16G16B16A16_TYPELESS);
            ENUM_MAP(eDataFormat_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT);
            ENUM_MAP(eDataFormat_R16G16B16A16_UNORM, DXGI_FORMAT_R16G16B16A16_UNORM);
            ENUM_MAP(eDataFormat_R16G16B16A16_UINT, DXGI_FORMAT_R16G16B16A16_UINT);
            ENUM_MAP(eDataFormat_R16G16B16A16_SNORM, DXGI_FORMAT_R16G16B16A16_SNORM);
            ENUM_MAP(eDataFormat_R16G16B16A16_SINT, DXGI_FORMAT_R16G16B16A16_SINT);
            ENUM_MAP(eDataFormat_R32G32_TYPELESS, DXGI_FORMAT_R32G32_TYPELESS);
            ENUM_MAP(eDataFormat_R32G32_FLOAT, DXGI_FORMAT_R32G32_FLOAT);
            ENUM_MAP(eDataFormat_R32G32_UINT, DXGI_FORMAT_R32G32_UINT);
            ENUM_MAP(eDataFormat_R32G32_SINT, DXGI_FORMAT_R32G32_SINT);
            ENUM_MAP(eDataFormat_R32G8X24_TYPELESS, DXGI_FORMAT_R32G8X24_TYPELESS);
            ENUM_MAP(eDataFormat_D32_FLOAT_S8X24_UINT, DXGI_FORMAT_D32_FLOAT_S8X24_UINT);
            ENUM_MAP(eDataFormat_R32_FLOAT_X8X24_TYPELESS, DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS);
            ENUM_MAP(eDataFormat_X32_TYPELESS_G8X24_UINT, DXGI_FORMAT_X32_TYPELESS_G8X24_UINT);
            ENUM_MAP(eDataFormat_R10G10B10A2_TYPELESS, DXGI_FORMAT_R10G10B10A2_TYPELESS);
            ENUM_MAP(eDataFormat_R10G10B10A2_UNORM, DXGI_FORMAT_R10G10B10A2_UNORM);
            ENUM_MAP(eDataFormat_R10G10B10A2_UINT, DXGI_FORMAT_R10G10B10A2_UINT);
            ENUM_MAP(eDataFormat_R11G11B10_FLOAT, DXGI_FORMAT_R11G11B10_FLOAT);
            ENUM_MAP(eDataFormat_R8G8B8A8_TYPELESS, DXGI_FORMAT_R8G8B8A8_TYPELESS);
            ENUM_MAP(eDataFormat_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM);            
            ENUM_MAP(eDataFormat_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB);
            ENUM_MAP(eDataFormat_R8G8B8A8_UINT, DXGI_FORMAT_R8G8B8A8_UINT);
            ENUM_MAP(eDataFormat_R8G8B8A8_SNORM, DXGI_FORMAT_R8G8B8A8_SNORM);
            ENUM_MAP(eDataFormat_R8G8B8A8_SINT, DXGI_FORMAT_R8G8B8A8_SINT);
            ENUM_MAP(eDataFormat_R16G16_TYPELESS, DXGI_FORMAT_R16G16_TYPELESS);
            ENUM_MAP(eDataFormat_R16G16_FLOAT, DXGI_FORMAT_R16G16_FLOAT);
            ENUM_MAP(eDataFormat_R16G16_UNORM, DXGI_FORMAT_R16G16_UNORM);
            ENUM_MAP(eDataFormat_R16G16_UINT, DXGI_FORMAT_R16G16_UINT);
            ENUM_MAP(eDataFormat_R16G16_SNORM, DXGI_FORMAT_R16G16_SNORM);
            ENUM_MAP(eDataFormat_R16G16_SINT, DXGI_FORMAT_R16G16_SINT);
            ENUM_MAP(eDataFormat_R32_TYPELESS, DXGI_FORMAT_R32_TYPELESS);
            ENUM_MAP(eDataFormat_D32_FLOAT, DXGI_FORMAT_D32_FLOAT);
            ENUM_MAP(eDataFormat_R32_FLOAT, DXGI_FORMAT_R32_FLOAT);
            ENUM_MAP(eDataFormat_R32_UINT, DXGI_FORMAT_R32_UINT);
            ENUM_MAP(eDataFormat_R32_SINT, DXGI_FORMAT_R32_SINT);
            ENUM_MAP(eDataFormat_R24G8_TYPELESS, DXGI_FORMAT_R24G8_TYPELESS);
            ENUM_MAP(eDataFormat_D24_UNORM_S8_UINT, DXGI_FORMAT_D24_UNORM_S8_UINT);
            ENUM_MAP(eDataFormat_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
            ENUM_MAP(eDataFormat_X24_TYPELESS_G8_UINT, DXGI_FORMAT_X24_TYPELESS_G8_UINT);
            ENUM_MAP(eDataFormat_R8G8_TYPELESS, DXGI_FORMAT_R8G8_TYPELESS);
            ENUM_MAP(eDataFormat_R8G8_UNORM, DXGI_FORMAT_R8G8_UNORM);
            ENUM_MAP(eDataFormat_R8G8_UINT, DXGI_FORMAT_R8G8_UINT);
            ENUM_MAP(eDataFormat_R8G8_SNORM, DXGI_FORMAT_R8G8_SNORM);
            ENUM_MAP(eDataFormat_R8G8_SINT, DXGI_FORMAT_R8G8_SINT);
            ENUM_MAP(eDataFormat_R16_TYPELESS, DXGI_FORMAT_R16_TYPELESS);
            ENUM_MAP(eDataFormat_R16_FLOAT, DXGI_FORMAT_R16_FLOAT);
            ENUM_MAP(eDataFormat_D16_UNORM, DXGI_FORMAT_D16_UNORM);
            ENUM_MAP(eDataFormat_R16_UNORM, DXGI_FORMAT_R16_UNORM);
            ENUM_MAP(eDataFormat_R16_UINT, DXGI_FORMAT_R16_UINT);
            ENUM_MAP(eDataFormat_R16_SNORM, DXGI_FORMAT_R16_SNORM);
            ENUM_MAP(eDataFormat_R16_SINT, DXGI_FORMAT_R16_SINT);
            ENUM_MAP(eDataFormat_R8_TYPELESS, DXGI_FORMAT_R8_TYPELESS);
            ENUM_MAP(eDataFormat_R8_UNORM, DXGI_FORMAT_R8_UNORM);
            ENUM_MAP(eDataFormat_R8_UINT, DXGI_FORMAT_R8_UINT);
            ENUM_MAP(eDataFormat_R8_SNORM, DXGI_FORMAT_R8_SNORM);
            ENUM_MAP(eDataFormat_R8_SINT, DXGI_FORMAT_R8_SINT);
            ENUM_MAP(eDataFormat_A8_UNORM, DXGI_FORMAT_A8_UNORM);
            ENUM_MAP(eDataFormat_R1_UNORM, DXGI_FORMAT_R1_UNORM);
            ENUM_MAP(eDataFormat_R9G9B9E5_SHAREDEXP, DXGI_FORMAT_R9G9B9E5_SHAREDEXP);
            ENUM_MAP(eDataFormat_R8G8_B8G8_UNORM, DXGI_FORMAT_R8G8_B8G8_UNORM);
            ENUM_MAP(eDataFormat_G8R8_G8B8_UNORM, DXGI_FORMAT_G8R8_G8B8_UNORM);
            ENUM_MAP(eDataFormat_BC1_TYPELESS, DXGI_FORMAT_BC1_TYPELESS);
            ENUM_MAP(eDataFormat_BC1_UNORM, DXGI_FORMAT_BC1_UNORM);
            ENUM_MAP(eDataFormat_BC1_UNORM_SRGB, DXGI_FORMAT_BC1_UNORM_SRGB);
            ENUM_MAP(eDataFormat_BC2_TYPELESS, DXGI_FORMAT_BC2_TYPELESS);
            ENUM_MAP(eDataFormat_BC2_UNORM, DXGI_FORMAT_BC2_UNORM);
            ENUM_MAP(eDataFormat_BC2_UNORM_SRGB, DXGI_FORMAT_BC2_UNORM_SRGB);
            ENUM_MAP(eDataFormat_BC3_TYPELESS, DXGI_FORMAT_BC3_TYPELESS);
            ENUM_MAP(eDataFormat_BC3_UNORM, DXGI_FORMAT_BC3_UNORM);
            ENUM_MAP(eDataFormat_BC3_UNORM_SRGB, DXGI_FORMAT_BC3_UNORM_SRGB);
            ENUM_MAP(eDataFormat_BC4_TYPELESS, DXGI_FORMAT_BC4_TYPELESS);
            ENUM_MAP(eDataFormat_BC4_UNORM, DXGI_FORMAT_BC4_UNORM);
            ENUM_MAP(eDataFormat_BC4_SNORM, DXGI_FORMAT_BC4_SNORM);
            ENUM_MAP(eDataFormat_BC5_TYPELESS, DXGI_FORMAT_BC5_TYPELESS);
            ENUM_MAP(eDataFormat_BC5_UNORM, DXGI_FORMAT_BC5_UNORM);
            ENUM_MAP(eDataFormat_BC5_SNORM, DXGI_FORMAT_BC5_SNORM);
            ENUM_MAP(eDataFormat_B5G6R5_UNORM, DXGI_FORMAT_B5G6R5_UNORM);
            ENUM_MAP(eDataFormat_B5G5R5A1_UNORM, DXGI_FORMAT_B5G5R5A1_UNORM);
            ENUM_MAP(eDataFormat_B8G8R8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM);
            ENUM_MAP(eDataFormat_B8G8R8X8_UNORM, DXGI_FORMAT_B8G8R8X8_UNORM);
            ENUM_MAP(eDataFormat_R10G10B10_XR_BIAS_A2_UNORM, DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM);
            ENUM_MAP(eDataFormat_B8G8R8A8_TYPELESS, DXGI_FORMAT_B8G8R8A8_TYPELESS);
            ENUM_MAP(eDataFormat_B8G8R8A8_UNORM_SRGB, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB);
            ENUM_MAP(eDataFormat_B8G8R8X8_TYPELESS, DXGI_FORMAT_B8G8R8X8_TYPELESS);
            ENUM_MAP(eDataFormat_B8G8R8X8_UNORM_SRGB, DXGI_FORMAT_B8G8R8X8_UNORM_SRGB);
            ENUM_MAP(eDataFormat_BC6H_TYPELESS, DXGI_FORMAT_BC6H_TYPELESS);
            ENUM_MAP(eDataFormat_BC6H_UF16, DXGI_FORMAT_BC6H_UF16);
            ENUM_MAP(eDataFormat_BC6H_SF16, DXGI_FORMAT_BC6H_SF16);
            ENUM_MAP(eDataFormat_BC7_TYPELESS, DXGI_FORMAT_BC7_TYPELESS);
            ENUM_MAP(eDataFormat_BC7_UNORM, DXGI_FORMAT_BC7_UNORM);
            ENUM_MAP(eDataFormat_BC7_UNORM_SRGB, DXGI_FORMAT_BC7_UNORM_SRGB);
        }
        ENUM_MAP_DECL_END(eDataFormat, DXGI_FORMAT);

        ENUM_MAP_DECL_BEGIN(eCompareFunction, D3D12_COMPARISON_FUNC) {
            ENUM_MAP(eCompareFunction_Never, D3D12_COMPARISON_FUNC_NEVER);
            ENUM_MAP(eCompareFunction_LessThan, D3D12_COMPARISON_FUNC_LESS);
            ENUM_MAP(eCompareFunction_Equal, D3D12_COMPARISON_FUNC_EQUAL);
            ENUM_MAP(eCompareFunction_LessOrEqual, D3D12_COMPARISON_FUNC_LESS_EQUAL);
            ENUM_MAP(eCompareFunction_GreaterThan, D3D12_COMPARISON_FUNC_GREATER);
            ENUM_MAP(eCompareFunction_NotEqual, D3D12_COMPARISON_FUNC_NOT_EQUAL);
            ENUM_MAP(eCompareFunction_GreaterOrEqual, D3D12_COMPARISON_FUNC_GREATER_EQUAL);
            ENUM_MAP(eCompareFunction_Always, D3D12_COMPARISON_FUNC_ALWAYS);
        }
        ENUM_MAP_DECL_END(eCompareFunction, D3D12_COMPARISON_FUNC);

ENUM_MAP_DECL_BEGIN(eStaticBorderColor, D3D12_STATIC_BORDER_COLOR) {
ENUM_MAP(eStaticBorderColor_Transparent_Black, D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK);
ENUM_MAP(eStaticBorderColor_Opaque_Black, D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK);
ENUM_MAP(eStaticBorderColor_Opaque_White, D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE);
} ENUM_MAP_DECL_END(eStaticBorderColor, D3D12_STATIC_BORDER_COLOR);

ENUM_MAP_DECL_BEGIN(eShaderVisibility, D3D12_SHADER_VISIBILITY) {
ENUM_MAP(eShaderVisibility_All, D3D12_SHADER_VISIBILITY_ALL);
ENUM_MAP(eShaderVisibility_Vertex, D3D12_SHADER_VISIBILITY_VERTEX);
ENUM_MAP(eShaderVisibility_Hull, D3D12_SHADER_VISIBILITY_HULL);
ENUM_MAP(eShaderVisibility_Domain, D3D12_SHADER_VISIBILITY_DOMAIN);
ENUM_MAP(eShaderVisibility_Geometry, D3D12_SHADER_VISIBILITY_GEOMETRY);
ENUM_MAP(eShaderVisibility_Pixel, D3D12_SHADER_VISIBILITY_PIXEL);
} ENUM_MAP_DECL_END(eShaderVisibility, D3D12_SHADER_VISIBILITY);

ENUM_MAP_DECL_BEGIN(eRootParameterType, D3D12_ROOT_PARAMETER_TYPE) {
ENUM_MAP(eRootParameterType_Descriptor_Table, D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE);
ENUM_MAP(eRootParameterType_32Bit_Constants, D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS);
ENUM_MAP(eRootParameterType_Cbv, D3D12_ROOT_PARAMETER_TYPE_CBV);
ENUM_MAP(eRootParameterType_Srv, D3D12_ROOT_PARAMETER_TYPE_SRV);
ENUM_MAP(eRootParameterType_Uav, D3D12_ROOT_PARAMETER_TYPE_UAV);
} ENUM_MAP_DECL_END(eRootParameterType, D3D12_ROOT_PARAMETER_TYPE);

ENUM_MAP_DECL_BEGIN(eDescriptorRangeType, D3D12_DESCRIPTOR_RANGE_TYPE) {
ENUM_MAP(eDescriptorRangeType_Srv, D3D12_DESCRIPTOR_RANGE_TYPE_SRV);
ENUM_MAP(eDescriptorRangeType_Uav, D3D12_DESCRIPTOR_RANGE_TYPE_UAV);
ENUM_MAP(eDescriptorRangeType_Cbv, D3D12_DESCRIPTOR_RANGE_TYPE_CBV);
ENUM_MAP(eDescriptorRangeType_Sampler, D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER);
} ENUM_MAP_DECL_END(eDescriptorRangeType, D3D12_DESCRIPTOR_RANGE_TYPE);
 
        ENUM_MAP_DECL_BEGIN(eDepthWriteMask, D3D12_DEPTH_WRITE_MASK) {
            ENUM_MAP(eDepthWriteMask_Zero, D3D12_DEPTH_WRITE_MASK_ZERO);
            ENUM_MAP(eDepthWriteMask_All, D3D12_DEPTH_WRITE_MASK_ALL);
        }
        ENUM_MAP_DECL_END(eDepthWriteMask, D3D12_DEPTH_WRITE_MASK);

        ENUM_MAP_DECL_BEGIN(eStencilOperation, D3D12_STENCIL_OP) {
            ENUM_MAP(eStencilOperation_Keep, D3D12_STENCIL_OP_KEEP);
            ENUM_MAP(eStencilOperation_Zero, D3D12_STENCIL_OP_ZERO);
            ENUM_MAP(eStencilOperation_Replace, D3D12_STENCIL_OP_REPLACE);
            ENUM_MAP(eStencilOperation_IncrementClamp, D3D12_STENCIL_OP_INCR_SAT);
            ENUM_MAP(eStencilOperation_DecrementClamp, D3D12_STENCIL_OP_DECR_SAT);
            ENUM_MAP(eStencilOperation_Invert, D3D12_STENCIL_OP_INVERT);
            ENUM_MAP(eStencilOperation_IncrementWrap, D3D12_STENCIL_OP_INCR);
            ENUM_MAP(eStencilOperation_DecrementWrap, D3D12_STENCIL_OP_DECR);
        }
        ENUM_MAP_DECL_END(eStencilOperation, D3D12_STENCIL_OP);

        ENUM_MAP_DECL_BEGIN(ePrimitiveTopologyType, D3D12_PRIMITIVE_TOPOLOGY_TYPE) {
            ENUM_MAP(ePrimitiveTopologyType_Point, D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT);
            ENUM_MAP(ePrimitiveTopologyType_Line, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);
            ENUM_MAP(ePrimitiveTopologyType_Triangle, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
            ENUM_MAP(ePrimitiveTopologyType_Patch, D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH);
        }        
        ENUM_MAP_DECL_END(ePrimitiveTopologyType, D3D12_PRIMITIVE_TOPOLOGY_TYPE);

        ENUM_MAP_DECL_BEGIN(eRootSignatureFlag, D3D12_ROOT_SIGNATURE_FLAGS) {
            case eRootSignatureFlag_None:
                return (D3D12_ROOT_SIGNATURE_FLAG_NONE);
            default:
                return (D3D12_ROOT_SIGNATURE_FLAGS)value;
        }        
        ENUM_MAP_DECL_END(eRootSignatureFlag, D3D12_ROOT_SIGNATURE_FLAGS);

        ENUM_MAP_DECL_BEGIN(eFilterType, D3D12_FILTER) {
            ENUM_MAP(eFiltertype_Min_Mag_Mip_Point, D3D12_FILTER_MIN_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Min_Mag_Point_Mip_Linear, D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Min_Point_Mag_Linear_Mip_Point, D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Min_Point_Mag_Mip_Linear, D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Min_Linear_Mag_Mip_Point, D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Min_Linear_Mag_Point_Mip_Linear, D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Min_Mag_Linear_Mip_Point, D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Min_Mag_Mip_Linear, D3D12_FILTER_MIN_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Anisotropic, D3D12_FILTER_ANISOTROPIC);
            ENUM_MAP(eFiltertype_Comparison_Min_Mag_Mip_Point, D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Comparison_Min_Mag_Point_Mip_Linear, D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Comparison_Min_Point_Mag_Linear_Mip_Point, D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Comparison_Min_Point_Mag_Mip_Linear, D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Comparison_Min_Linear_Mag_Mip_Point, D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Comparison_Min_Linear_Mag_Point_Mip_Linear, D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Comparison_Min_Mag_Linear_Mip_Point, D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Comparison_Min_Mag_Mip_Linear, D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Comparison_Anisotropic, D3D12_FILTER_COMPARISON_ANISOTROPIC);
            ENUM_MAP(eFiltertype_Minimum_Min_Mag_Mip_Point, D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Minimum_Min_Mag_Point_Mip_Linear, D3D12_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Minimum_Min_Point_Mag_Linear_Mip_Point, D3D12_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Minimum_Min_Point_Mag_Mip_Linear, D3D12_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Minimum_Min_Linear_Mag_Mip_Point, D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Minimum_Min_Linear_Mag_Point_Mip_Linear, D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Minimum_Min_Mag_Linear_Mip_Point, D3D12_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Minimum_Min_Mag_Mip_Linear, D3D12_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Minimum_Anisotropic, D3D12_FILTER_MINIMUM_ANISOTROPIC);
            ENUM_MAP(eFiltertype_Maximum_Min_Mag_Mip_Point, D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Maximum_Min_Mag_Point_Mip_Linear, D3D12_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Maximum_Min_Point_Mag_Linear_Mip_Point, D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Maximum_Min_Point_Mag_Mip_Linear, D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Maximum_Min_Linear_Mag_Mip_Point, D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT);
            ENUM_MAP(eFiltertype_Maximum_Min_Linear_Mag_Point_Mip_Linear, D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Maximum_Min_Mag_Linear_Mip_Point, D3D12_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT);
            ENUM_MAP(eFiltertype_Maximum_Min_Mag_Mip_Linear, D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR);
            ENUM_MAP(eFiltertype_Maximum_Anisotropic, D3D12_FILTER_MAXIMUM_ANISOTROPIC);
        } 
        ENUM_MAP_DECL_END(eFilterType, D3D12_FILTER);

        ENUM_MAP_DECL_BEGIN(eTextureAddressMode, D3D12_TEXTURE_ADDRESS_MODE) {
            ENUM_MAP(eTextureAddressMode_Wrap, D3D12_TEXTURE_ADDRESS_MODE_WRAP);
            ENUM_MAP(eTextureAddressMode_Mirror, D3D12_TEXTURE_ADDRESS_MODE_MIRROR);
            ENUM_MAP(eTextureAddressMode_Clamp, D3D12_TEXTURE_ADDRESS_MODE_CLAMP);
            ENUM_MAP(eTextureAddressMode_Border, D3D12_TEXTURE_ADDRESS_MODE_BORDER);
            ENUM_MAP(eTextureAddressMode_Mirror_Once, D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE);
        } ENUM_MAP_DECL_END(eTextureAddressMode, D3D12_TEXTURE_ADDRESS_MODE);

        ENUM_MAP_DECL_BEGIN(ePrimitiveType, D3D12_PRIMITIVE_TOPOLOGY) {     
            ENUM_MAP(ePrimitiveType_PointList, D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
            ENUM_MAP(ePrimitiveType_LineList, D3D_PRIMITIVE_TOPOLOGY_LINELIST);
            ENUM_MAP(ePrimitiveType_LineStrip, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
            ENUM_MAP(ePrimitiveType_TriangleList, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            ENUM_MAP(ePrimitiveType_TriangleStrip, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); 
            ENUM_MAP(ePrimitivetype_LineList_Adj, D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ);
            ENUM_MAP(ePrimitivetype_LineStrip_Adj, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
            ENUM_MAP(ePrimitivetype_TriangleList_Adj, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
            ENUM_MAP(ePrimitivetype_TriangleStrip_Adj, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);
            ENUM_MAP(ePrimitivetype_1_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_2_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_3_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_4_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_5_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_6_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_7_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_8_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_9_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_10_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_11_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_12_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_13_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_14_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_15_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_16_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_17_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_18_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_19_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_20_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_21_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_22_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_23_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_24_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_25_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_26_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_27_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_28_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_29_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_30_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_31_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST);
            ENUM_MAP(ePrimitivetype_32_Control_Point_Patchlist, D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST);
        }
        ENUM_MAP_DECL_END(ePrimitiveType, D3D12_PRIMITIVE_TOPOLOGY);

        ENUM_MAP_DECL_BEGIN(ePolygonFillMode, D3D12_FILL_MODE) {
            ENUM_MAP(ePolygonFillMode_Wireframe, D3D12_FILL_MODE_WIREFRAME);
            ENUM_MAP(ePolygonFillMode_Solid, D3D12_FILL_MODE_SOLID);
        }
        ENUM_MAP_DECL_END(ePolygonFillMode, D3D12_FILL_MODE);

        ENUM_MAP_DECL_BEGIN(ePolygonCullMode, D3D12_CULL_MODE) {
            ENUM_MAP(ePolygonCullMode_None, D3D12_CULL_MODE_NONE);
            ENUM_MAP(ePolygonCullMode_Front, D3D12_CULL_MODE_FRONT);
            ENUM_MAP(ePolygonCullMode_Back, D3D12_CULL_MODE_BACK);
        }
        ENUM_MAP_DECL_END(ePolygonCullMode, D3D12_CULL_MODE);

        ENUM_MAP_DECL_BEGIN(eBlendType, D3D12_BLEND) {
                ENUM_MAP(eBlendType_Zero, D3D12_BLEND_ZERO);
                ENUM_MAP(eBlendType_One, D3D12_BLEND_ONE);
                ENUM_MAP(eBlendType_SourceColor, D3D12_BLEND_SRC_COLOR);
                ENUM_MAP(eBlendType_InverseSourceColor, D3D12_BLEND_INV_SRC_COLOR);
                ENUM_MAP(eBlendType_SourceAlpha, D3D12_BLEND_SRC_ALPHA);
                ENUM_MAP(eBlendType_InverseSourceAlpha, D3D12_BLEND_INV_SRC_ALPHA);
                ENUM_MAP(eBlendType_DestinationAlpha, D3D12_BLEND_DEST_ALPHA);
                ENUM_MAP(eBlendType_InverseDestinationAlpha, D3D12_BLEND_INV_DEST_ALPHA);
                ENUM_MAP(eBlendType_DestinationColor, D3D12_BLEND_DEST_COLOR);
                ENUM_MAP(eBlendType_InverseDestinationColor, D3D12_BLEND_INV_DEST_COLOR);
                ENUM_MAP(eBlendType_SourceAlphaSaturation, D3D12_BLEND_SRC_ALPHA_SAT);
                ENUM_MAP(eBlendType_BlendFactor, D3D12_BLEND_BLEND_FACTOR);
                ENUM_MAP(eBlendType_InverseBlendFactor, D3D12_BLEND_INV_SRC1_ALPHA);
                ENUM_MAP(eBlendType_SourceOneColor, D3D12_BLEND_SRC1_COLOR);
                ENUM_MAP(eBlendType_InverseSourceOneColor, D3D12_BLEND_INV_SRC1_COLOR);
                ENUM_MAP(eBlendType_SourceOneAlpha, D3D12_BLEND_SRC1_ALPHA);
                ENUM_MAP(eBlendType_InverseSourceOneAlpha, D3D12_BLEND_INV_SRC1_ALPHA);
        }
        ENUM_MAP_DECL_END(eBlendType, D3D12_BLEND);

        ENUM_MAP_DECL_BEGIN(eBlendOperation, D3D12_BLEND_OP) {
            ENUM_MAP(eBlendOperation_Add, D3D12_BLEND_OP_ADD);
            ENUM_MAP(eBlendOperation_Subtract, D3D12_BLEND_OP_SUBTRACT);
            ENUM_MAP(eBlendOperation_ReverseSubtract, D3D12_BLEND_OP_REV_SUBTRACT);
            ENUM_MAP(eBlendOperation_Min, D3D12_BLEND_OP_MIN);
            ENUM_MAP(eBlendOperation_Max, D3D12_BLEND_OP_MAX);
        }
        ENUM_MAP_DECL_END(eBlendOperation, D3D12_BLEND_OP);

        ENUM_MAP_DECL_BEGIN(eBlendLogicOperation, D3D12_LOGIC_OP) {            
            ENUM_MAP(eBlendLogicOperation_Clear, D3D12_LOGIC_OP_CLEAR);
            ENUM_MAP(eBlendLogicOperation_Set, D3D12_LOGIC_OP_SET);
            ENUM_MAP(eBlendLogicOperation_Copy, D3D12_LOGIC_OP_COPY);
            ENUM_MAP(eBlendLogicOperation_CopyInverted, D3D12_LOGIC_OP_COPY_INVERTED);             
            ENUM_MAP(eBlendLogicOperation_Nothing, D3D12_LOGIC_OP_NOOP);
            ENUM_MAP(eBlendLogicOperation_Invert, D3D12_LOGIC_OP_INVERT);
            ENUM_MAP(eBlendLogicOperation_And, D3D12_LOGIC_OP_AND);
            ENUM_MAP(eBlendLogicOperation_NotAnd, D3D12_LOGIC_OP_NAND);
            ENUM_MAP(eBlendLogicOperation_Or, D3D12_LOGIC_OP_OR);
            ENUM_MAP(eBlendLogicOperation_NotOr, D3D12_LOGIC_OP_NOR);
            ENUM_MAP(eBlendLogicOperation_Xor, D3D12_LOGIC_OP_XOR);
            ENUM_MAP(eBlendLogicOperation_Equal, D3D12_LOGIC_OP_EQUIV);
            ENUM_MAP(eBlendLogicOperation_AndReverse, D3D12_LOGIC_OP_AND_REVERSE);
            ENUM_MAP(eBlendLogicOperation_AndInverted, D3D12_LOGIC_OP_AND_INVERTED);
            ENUM_MAP(eBlendLogicOperation_OrReverse, D3D12_LOGIC_OP_OR_REVERSE);
            ENUM_MAP(eBlendLogicOperation_OrInverted, D3D12_LOGIC_OP_OR_INVERTED);            
        }
        ENUM_MAP_DECL_END(eBlendLogicOperation, D3D12_LOGIC_OP);

        ENUM_MAP_DECL_BEGIN(eIndexBufferStripCutValue, D3D12_INDEX_BUFFER_STRIP_CUT_VALUE) {            
            ENUM_MAP(eIndexBufferStripCutValue_Disabled, D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED);           
            ENUM_MAP(eIndexBufferStripCutValue_0xFFFF, D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF);           
            ENUM_MAP(eIndexBufferStripCutValue_0xFFFFFFFF, D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF);
        }         
        ENUM_MAP_DECL_END(eIndexBufferStripCutValue, D3D12_INDEX_BUFFER_STRIP_CUT_VALUE);

        
    }
}
 
namespace sly {
    namespace gfx {  

        template<typename TSrc, typename TDest, typename std::enable_if<std::is_convertible<TSrc, TDest>::value, int>::type = 0>
        inline void D3DAssign(TDest& dest, const TSrc src) {
            dest = src;
        }

        inline void D3DAssign(BOOL& dest, bool_t src) {
            dest = src;
        }      

        template<typename TSrc, typename TDest, typename std::enable_if<std::is_enum<TDest>::value, int>::type = 0>
        inline void D3DAssign(TDest& dest, TSrc src) {
            enum_convert_assign(src, dest);
        }  

        template<typename TDest, typename TSrc, typename std::enable_if<std::is_enum<TDest>::value, int>::type = 0>
        inline TDest D3DConvert(TSrc src) {
            return enum_convert_to<TDest>(src);
        }    

        D3D_DECL_CAST(D3D12_VIEWPORT, Viewport, 
            this->Height = src.height;
            this->Width = src.width;
            this->TopLeftX = src.x;
            this->TopLeftY = src.y;
            this->MinDepth = src.maxDepth;
            this->MaxDepth = src.minDepth;
        );
        
        D3D_DECL_CAST(D3D12_RECT, rect_t<real_t>,
            this->left = (LONG)src.left();
            this->top = (LONG)src.top();
            this->right = (LONG)src.right();
            this->bottom = (LONG)src.bottom();
        );

       D3D_DECL_CAST(D3D12_INPUT_ELEMENT_DESC, InputElementDesc,
            this->SemanticName = src.semanticName.c_str();
            this->SemanticIndex = 0;
            this->InstanceDataStepRate = 0;
            this->InputSlot = 0;
            this->AlignedByteOffset = (UINT)src.offset;
            this->InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
            this->Format = enum_convert_to<DXGI_FORMAT>(src.format);
        );

        D3D_DECL_CAST(D3D12_DEPTH_STENCILOP_DESC, DepthStencilOperationDesc,
            D3DAssign(this->StencilFailOp, src.stencilFailOp);
            D3DAssign(this->StencilDepthFailOp, src.stencilDepthFailOp);
            D3DAssign(this->StencilPassOp, src.stencilPassOp);
            D3DAssign(this->StencilFunc, src.stencilFunc);
        );

        D3D_DECL_CAST(D3D12_DEPTH_STENCIL_DESC, DepthStencilDesc,
            D3DAssign(this->DepthEnable, src.depthEnable);
            D3DAssign(this->DepthWriteMask, src.depthWriteMask);
            D3DAssign(this->DepthFunc ,src.depthFunc);
            D3DAssign(this->StencilEnable,src.stencilEnable);
            D3DAssign(this->StencilReadMask,src.stencilReadMask);
            D3DAssign(this->StencilWriteMask, src.stencilWriteMask);
            D3DAssign(this->FrontFace, src.frontFace);
            D3DAssign(this->BackFace, src.backFace);                
        );

        D3D_DECL_CAST(DXGI_SAMPLE_DESC, SampleDesc,
            D3DAssign(this->Count, src.count);
            D3DAssign(this->Quality, src.quality);               
        );

        D3D_DECL_CAST(D3D12_RASTERIZER_DESC, RasterizerStateDesc, 
            D3DAssign(FillMode, src.fillMode);
            D3DAssign(CullMode, src.cullMode);
            D3DAssign(FrontCounterClockwise, src.frontCounterClockwise);
            D3DAssign(DepthBias, src.depthBias);
            D3DAssign(DepthBiasClamp, src.depthBiasClamp);
            D3DAssign(SlopeScaledDepthBias, src.slopeScaledDepthBias);
            D3DAssign(DepthClipEnable, src.depthClipEnable);
            D3DAssign(MultisampleEnable, src.multisampleEnable);
            D3DAssign(AntialiasedLineEnable, src.antialiasedLineEnable);
            D3DAssign(ForcedSampleCount, src.forcedSampleCount);
            ConservativeRaster = src.conservativeRaster ? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON : D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
        );
            
        D3D_DECL_CAST(D3D12_RENDER_TARGET_BLEND_DESC, BlendTargetDesc, 
            
            D3DAssign(BlendEnable, src.blendEnable);
            D3DAssign(LogicOpEnable, src.logicOpEnable);
            D3DAssign(SrcBlend, src.srcBlend);
            D3DAssign(DestBlend, src.destBlend);
            D3DAssign(BlendOp, src.blendOp);
            D3DAssign(SrcBlendAlpha, src.srcBlendAlpha);
            D3DAssign(DestBlendAlpha, src.destBlendAlpha);
            D3DAssign(BlendOpAlpha, src.blendOpAlpha);
            D3DAssign(LogicOp, src.logicOp);
            D3DAssign(RenderTargetWriteMask, src.renderTargetWriteMask);
        );           

        D3D_DECL_CAST(D3D12_BLEND_DESC, BlendStateDesc, 
            D3DAssign(AlphaToCoverageEnable, src.alphaToCoverageEnable);
            D3DAssign(IndependentBlendEnable, src.independentBlendEnable);
            //D3DAssign(NumBlendTargets, src.numBlendTargets);

            Expects(src.numBlendTargets <= 8);
            for(size_t i = 0; i < 8; i++) {
                D3DAssign(RenderTarget[i], src.targets[i]);
            }
        );

        D3D_DECL_CAST(D3D12_STREAM_OUTPUT_DESC, RenderStateStreamOutput, 
            D3DAssign(NumEntries, (UINT)src.streamOutputDeclaration.size());
            D3DAssign(NumStrides, (UINT)src.bufferStrides.size());
        );

        D3D_DECL_CAST(D3D12_ROOT_SIGNATURE_DESC, RootSignatureDesc,
            D3DAssign(NumParameters, (UINT)src.parameters.size());
            D3DAssign(NumStaticSamplers, (UINT)src.staticSamplers.size());
            D3DAssign(Flags, src.flags);     
        );

        D3D_DECL_CAST(D3D12_ROOT_DESCRIPTOR, RootDescriptorDesc,
            D3DAssign(ShaderRegister, src.shaderRegister);  
            D3DAssign(RegisterSpace, src.registerSpace);  
        );

        D3D_DECL_CAST(D3D12_DESCRIPTOR_RANGE, RootDescriptorRangeDesc,
            D3DAssign(NumDescriptors, src.numDescriptors);
            D3DAssign(BaseShaderRegister, src.baseShaderRegister);
            D3DAssign(RegisterSpace, src.registerSpace);
            D3DAssign(OffsetInDescriptorsFromTableStart, src.offsetInDescriptorsFromTableStart);
            D3DAssign(RangeType, src.rangeType);  
        );

        D3D_DECL_CAST(D3D12_ROOT_CONSTANTS, RootConstantsDesc,
            D3DAssign(ShaderRegister, src.shaderRegister);  
            D3DAssign(RegisterSpace, src.registerSpace);   
            D3DAssign(Num32BitValues, src.num32BitValues);       
        );

        D3D_DECL_CAST(D3D12_ROOT_PARAMETER, RootParameterDesc,
            D3DAssign(ParameterType, src.parameterType);
            D3DAssign(ShaderVisibility, src.shaderVisibility);

            switch(src.parameterType) {
                case eRootParameterType_32Bit_Constants:
                    D3DAssign(Constants, src.constants);
                    break;
                case eRootParameterType_Cbv:
                case eRootParameterType_Srv:
                case eRootParameterType_Uav:
                    D3DAssign(Descriptor, src.descriptor);
                    break;          
            }
        );
                   
        D3D_DECL_CAST(D3D12_STATIC_SAMPLER_DESC, StaticSamplerDesc,
            D3DAssign(Filter, src.filter);
            D3DAssign( AddressU, src.addressU);
            D3DAssign( AddressV, src.addressV);
            D3DAssign( AddressW, src.addressW);
            D3DAssign( MipLODBias, src.mipLODBias);
            D3DAssign( MaxAnisotropy, src.maxAnisotropy);
            D3DAssign( ComparisonFunc, src.comparisonFunc);
            D3DAssign( BorderColor, src.borderColor);
            D3DAssign( MinLOD, src.minLOD);
            D3DAssign( MaxLOD, src.maxLOD);
            D3DAssign( ShaderRegister, src.shaderRegister);
            D3DAssign( RegisterSpace, src.registerSpace);
            D3DAssign( ShaderVisibility, src.shaderVisibility);
        );

        D3D_DECL_CAST(D3D12_GRAPHICS_PIPELINE_STATE_DESC, RenderStateDesc,
            D3DAssign(DepthStencilState, src.depthStencilState);
            D3DAssign(RasterizerState, src.rasterizerState);
            D3DAssign(BlendState, src.blend);
            D3DAssign(this->SampleDesc, src.sampleDesc);
            D3DAssign(SampleMask, src.sampleMax);
            D3DAssign(PrimitiveTopologyType, src.PrimitiveTopologyType);
            D3DAssign(NumRenderTargets, src.numberRenderTargets);
            D3DAssign(StreamOutput, src.streamOutput);
            D3DAssign(IBStripCutValue, src.indexBufferStripCutValue);
            D3DAssign(NodeMask, src.nodeMask);
            D3DAssign(DSVFormat, src.dsvFormat);
            
            
            InputLayout.NumElements = (uint_t)src.inputElements.size();

            GS = D3D12_SHADER_BYTECODE();
            HS = D3D12_SHADER_BYTECODE();
            DS = D3D12_SHADER_BYTECODE();
            
            if(src.vsShader) {    
                D3D12ShaderImpl* vsd3dShader = reinterpret_cast<D3D12ShaderImpl*>(src.vsShader);
                VS = { vsd3dShader->getBuffer(), (uint_t)vsd3dShader->getSizeInBytes() };
            }

            if(src.psShader) {    
                D3D12ShaderImpl* psd3dShader = reinterpret_cast<D3D12ShaderImpl*>(src.psShader);
                PS = { psd3dShader->getBuffer(), (uint_t)psd3dShader->getSizeInBytes() };
            }            
            
            for(size_t i = 0; i < src.numberRenderTargets; i++) {
                this->RTVFormats[i] = D3DConvert<DXGI_FORMAT>(src.rtvFormats[i]);
            } 

            for(size_t i = src.numberRenderTargets; i < 8; i++) {
                this->RTVFormats[i] = DXGI_FORMAT_UNKNOWN;
            }     
                         
        );      
    } 
}

