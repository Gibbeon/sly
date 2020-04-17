#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        ENUM_DECL(ePrimitiveType,  
            ePrimitiveType_PointList,
            ePrimitiveType_LineList,
            ePrimitiveType_LineStrip,
            ePrimitiveType_TriangleList,
            ePrimitiveType_TriangleStrip,
            ePrimitivetype_LineList_Adj,
            ePrimitivetype_LineStrip_Adj,
            ePrimitivetype_TriangleList_Adj,
            ePrimitivetype_TriangleStrip_Adj,
            ePrimitivetype_1_Control_Point_Patchlist,
            ePrimitivetype_2_Control_Point_Patchlist,
            ePrimitivetype_3_Control_Point_Patchlist,
            ePrimitivetype_4_Control_Point_Patchlist,
            ePrimitivetype_5_Control_Point_Patchlist,
            ePrimitivetype_6_Control_Point_Patchlist,
            ePrimitivetype_7_Control_Point_Patchlist,
            ePrimitivetype_8_Control_Point_Patchlist,
            ePrimitivetype_9_Control_Point_Patchlist,
            ePrimitivetype_10_Control_Point_Patchlist,
            ePrimitivetype_11_Control_Point_Patchlist,
            ePrimitivetype_12_Control_Point_Patchlist,
            ePrimitivetype_13_Control_Point_Patchlist,
            ePrimitivetype_14_Control_Point_Patchlist,
            ePrimitivetype_15_Control_Point_Patchlist,
            ePrimitivetype_16_Control_Point_Patchlist,
            ePrimitivetype_17_Control_Point_Patchlist,
            ePrimitivetype_18_Control_Point_Patchlist,
            ePrimitivetype_19_Control_Point_Patchlist,
            ePrimitivetype_20_Control_Point_Patchlist,
            ePrimitivetype_21_Control_Point_Patchlist,
            ePrimitivetype_22_Control_Point_Patchlist,
            ePrimitivetype_23_Control_Point_Patchlist,
            ePrimitivetype_24_Control_Point_Patchlist,
            ePrimitivetype_25_Control_Point_Patchlist,
            ePrimitivetype_26_Control_Point_Patchlist,
            ePrimitivetype_27_Control_Point_Patchlist,
            ePrimitivetype_28_Control_Point_Patchlist,
            ePrimitivetype_29_Control_Point_Patchlist,
            ePrimitivetype_30_Control_Point_Patchlist,
            ePrimitivetype_31_Control_Point_Patchlist,
            ePrimitivetype_32_Control_Point_Patchlist,
            ePrimitiveType_Max,
            ePrimitiveType_Default = ePrimitiveType_TriangleList
        );
        ENUM_DECL(ePrimitiveTopologyType,  
            ePrimitiveTopologyType_Point,
            ePrimitiveTopologyType_Line,
            ePrimitiveTopologyType_Triangle,
            ePrimitiveTopologyType_Patch,
            ePrimitiveTopologyType_Max,
            ePrimitiveTopologyType_Default = ePrimitiveTopologyType_Triangle
        );

        
        ENUM_DECL(eRootSignatureFlag,
            eRootSignatureFlag_None	= 0,
            eRootSignatureFlag_Allow_InputAssemblerInputLayout = 0x1,
            eRootSignatureFlag_Deny_VertexShaderRootAccess = 0x2,
            eRootSignatureFlag_Deny_HullShaderRootAccess = 0x4,
            eRootSignatureFlag_Deny_DomainShaderRootAccess = 0x8,
            eRootSignatureFlag_Deny_GeometryShaderRootAccess = 0x10,
            eRootSignatureFlag_Deny_PixelShaderRootAccess = 0x20,
            eRootSignatureFlag_Allow_StreamOutput = 0x40,
            eRootSignatureFlag_LocalRootSignature = 0x80
        ); 

        ENUM_DECL(eFilterType,
            eFiltertype_Min_Mag_Mip_Point,
            eFiltertype_Min_Mag_Point_Mip_Linear,
            eFiltertype_Min_Point_Mag_Linear_Mip_Point,
            eFiltertype_Min_Point_Mag_Mip_Linear,
            eFiltertype_Min_Linear_Mag_Mip_Point,
            eFiltertype_Min_Linear_Mag_Point_Mip_Linear,
            eFiltertype_Min_Mag_Linear_Mip_Point,
            eFiltertype_Min_Mag_Mip_Linear,
            eFiltertype_Anisotropic,
            eFiltertype_Comparison_Min_Mag_Mip_Point,
            eFiltertype_Comparison_Min_Mag_Point_Mip_Linear,
            eFiltertype_Comparison_Min_Point_Mag_Linear_Mip_Point,
            eFiltertype_Comparison_Min_Point_Mag_Mip_Linear,
            eFiltertype_Comparison_Min_Linear_Mag_Mip_Point,
            eFiltertype_Comparison_Min_Linear_Mag_Point_Mip_Linear,
            eFiltertype_Comparison_Min_Mag_Linear_Mip_Point,
            eFiltertype_Comparison_Min_Mag_Mip_Linear,
            eFiltertype_Comparison_Anisotropic,
            eFiltertype_Minimum_Min_Mag_Mip_Point,
            eFiltertype_Minimum_Min_Mag_Point_Mip_Linear,
            eFiltertype_Minimum_Min_Point_Mag_Linear_Mip_Point,
            eFiltertype_Minimum_Min_Point_Mag_Mip_Linear,
            eFiltertype_Minimum_Min_Linear_Mag_Mip_Point,
            eFiltertype_Minimum_Min_Linear_Mag_Point_Mip_Linear,
            eFiltertype_Minimum_Min_Mag_Linear_Mip_Point,
            eFiltertype_Minimum_Min_Mag_Mip_Linear,
            eFiltertype_Minimum_Anisotropic,
            eFiltertype_Maximum_Min_Mag_Mip_Point,
            eFiltertype_Maximum_Min_Mag_Point_Mip_Linear,
            eFiltertype_Maximum_Min_Point_Mag_Linear_Mip_Point,
            eFiltertype_Maximum_Min_Point_Mag_Mip_Linear,
            eFiltertype_Maximum_Min_Linear_Mag_Mip_Point,
            eFiltertype_Maximum_Min_Linear_Mag_Point_Mip_Linear,
            eFiltertype_Maximum_Min_Mag_Linear_Mip_Point,
            eFiltertype_Maximum_Min_Mag_Mip_Linear,
            eFiltertype_Maximum_Anisotropic); 
            
            ENUM_DECL(eTextureAddressMode,
                eTextureAddressMode_Wrap,
                eTextureAddressMode_Mirror,
                eTextureAddressMode_Clamp,
                eTextureAddressMode_Border,
                eTextureAddressMode_Mirror_Once);

                ENUM_DECL(eStaticBorderColor,
eStaticBorderColor_Transparent_Black,
eStaticBorderColor_Opaque_Black,
eStaticBorderColor_Opaque_White);

ENUM_DECL(eShaderVisibility,
eShaderVisibility_All,
eShaderVisibility_Vertex,
eShaderVisibility_Hull,
eShaderVisibility_Domain,
eShaderVisibility_Geometry,
eShaderVisibility_Pixel);

ENUM_DECL(eRootParameterType,
eRootParameterType_Descriptor_Table,
eRootParameterType_32Bit_Constants,
eRootParameterType_Cbv,
eRootParameterType_Srv,
eRootParameterType_Uav);

ENUM_DECL(eDescriptorRangeType,
eDescriptorRangeType_Srv,
eDescriptorRangeType_Uav,
eDescriptorRangeType_Cbv,
eDescriptorRangeType_Sampler);
    }
}

/*
s_PresentRS.Reset(4, 2);
    s_PresentRS[0].InitAsDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0, 2);
    s_PresentRS[1].InitAsConstants(0, 6, D3D12_SHADER_VISIBILITY_ALL);
    s_PresentRS[2].InitAsBufferSRV(2, D3D12_SHADER_VISIBILITY_PIXEL);
    s_PresentRS[3].InitAsDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 0, 1);
    s_PresentRS.InitStaticSampler(0, SamplerLinearClampDesc);
    s_PresentRS.InitStaticSampler(1, SamplerPointClampDesc);
    s_PresentRS.Finalize(L"Present");

    SamplerLinearClampDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    SamplerLinearClampDesc.SetTextureAddressMode(D3D12_TEXTURE_ADDRESS_MODE_CLAMP);
    SamplerLinearClamp = SamplerLinearClampDesc.CreateDescriptor();

    SamplerPointClampDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
    SamplerPointClampDesc.SetTextureAddressMode(D3D12_TEXTURE_ADDRESS_MODE_CLAMP);
    SamplerPointClamp = SamplerPointClampDesc.CreateDescriptor();
    */