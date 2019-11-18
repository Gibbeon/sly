/*#pragma once 

#include <windows.h>
#include <initguid.h>
#include <METAL.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>

struct CD3DX12_DEFAULT {};
extern const DECLSPEC_SELECTANY CD3DX12_DEFAULT METAL_DEFAULT;

//------------------------------------------------------------------------------------------------
struct CD3DX12_RANGE : public METAL_RANGE
{
    CD3DX12_RANGE() = default;
    explicit CD3DX12_RANGE(const METAL_RANGE &o) :
        METAL_RANGE(o)
    {}
    CD3DX12_RANGE( 
        SIZE_T begin, 
        SIZE_T end )
    {
        Begin = begin;
        End = end;
    }
};

struct CD3DX12_RECT : public METAL_RECT
{
    CD3DX12_RECT() = default;
    explicit CD3DX12_RECT( const METAL_RECT& o ) :
        METAL_RECT( o )
    {}
    explicit CD3DX12_RECT(
        LONG Left,
        LONG Top,
        LONG Right,
        LONG Bottom )
    {
        left = Left;
        top = Top;
        right = Right;
        bottom = Bottom;
    }
};

struct CD3DX12_VIEWPORT : public METAL_VIEWPORT
{
    CD3DX12_VIEWPORT() = default;
    explicit CD3DX12_VIEWPORT( const METAL_VIEWPORT& o ) :
        METAL_VIEWPORT( o )
    {}
    explicit CD3DX12_VIEWPORT(
        FLOAT topLeftX,
        FLOAT topLeftY,
        FLOAT width,
        FLOAT height,
        FLOAT minDepth = METAL_MIN_DEPTH,
        FLOAT maxDepth = METAL_MAX_DEPTH )
    {
        TopLeftX = topLeftX;
        TopLeftY = topLeftY;
        Width = width;
        Height = height;
        MinDepth = minDepth;
        MaxDepth = maxDepth;
    }
    explicit CD3DX12_VIEWPORT(
        IMETALResource* pResource,
        UINT mipSlice = 0,
        FLOAT topLeftX = 0.0f,
        FLOAT topLeftY = 0.0f,
        FLOAT minDepth = METAL_MIN_DEPTH,
        FLOAT maxDepth = METAL_MAX_DEPTH )
    {
        auto desc  = pResource->GetDesc();
        const UINT64 SubresourceWidth = desc.Width >> mipSlice;
        const UINT64 SubresourceHeight = desc.Height >> mipSlice;
        switch (desc.Dimension)
        {
        case METAL_RESOURCE_DIMENSION_BUFFER:
            TopLeftX = topLeftX;
            TopLeftY = 0.0f;
            Width = desc.Width - topLeftX;
            Height = 1.0f;
            break;
        case METAL_RESOURCE_DIMENSION_TEXTURE1D:
            TopLeftX = topLeftX;
            TopLeftY = 0.0f;
            Width = (SubresourceWidth ? SubresourceWidth : 1.0f) - topLeftX;
            Height = 1.0f;
            break;
        case METAL_RESOURCE_DIMENSION_TEXTURE2D:
        case METAL_RESOURCE_DIMENSION_TEXTURE3D:
            TopLeftX = topLeftX;
            TopLeftY = topLeftY;
            Width = (SubresourceWidth ? SubresourceWidth : 1.0f) - topLeftX;
            Height = (SubresourceHeight ? SubresourceHeight: 1.0f) - topLeftY;
            break;
        default: break;
        }

        MinDepth = minDepth;
        MaxDepth = maxDepth;
    }
};


//------------------------------------------------------------------------------------------------
struct CD3DX12_HEAP_PROPERTIES : public METAL_HEAP_PROPERTIES
{
    CD3DX12_HEAP_PROPERTIES() = default;
    explicit CD3DX12_HEAP_PROPERTIES(const METAL_HEAP_PROPERTIES &o) :
        METAL_HEAP_PROPERTIES(o)
    {}
    CD3DX12_HEAP_PROPERTIES( 
        METAL_CPU_PAGE_PROPERTY cpuPageProperty, 
        METAL_MEMORY_POOL memoryPoolPreference,
        UINT creationNodeMask = 1, 
        UINT nodeMask = 1 )
    {
        Type = METAL_HEAP_TYPE_CUSTOM;
        CPUPageProperty = cpuPageProperty;
        MemoryPoolPreference = memoryPoolPreference;
        CreationNodeMask = creationNodeMask;
        VisibleNodeMask = nodeMask;
    }
    explicit CD3DX12_HEAP_PROPERTIES( 
        METAL_HEAP_TYPE type, 
        UINT creationNodeMask = 1, 
        UINT nodeMask = 1 )
    {
        Type = type;
        CPUPageProperty = METAL_CPU_PAGE_PROPERTY_UNKNOWN;
        MemoryPoolPreference = METAL_MEMORY_POOL_UNKNOWN;
        CreationNodeMask = creationNodeMask;
        VisibleNodeMask = nodeMask;
    }
    bool IsCPUAccessible() const
    {
        return Type == METAL_HEAP_TYPE_UPLOAD || Type == METAL_HEAP_TYPE_READBACK || (Type == METAL_HEAP_TYPE_CUSTOM &&
            (CPUPageProperty == METAL_CPU_PAGE_PROPERTY_WRITE_COMBINE || CPUPageProperty == METAL_CPU_PAGE_PROPERTY_WRITE_BACK));
    }
};
//------------------------------------------------------------------------------------------------
inline UINT8 METALGetFormatPlaneCount(
    _In_ IMETALDevice* pDevice,
    DXGI_FORMAT Format
    )
{
    METAL_FEATURE_DATA_FORMAT_INFO formatInfo = { Format, 0 };
    if (FAILED(pDevice->CheckFeatureSupport(METAL_FEATURE_FORMAT_INFO, &formatInfo, sizeof(formatInfo))))
    {
        return 0;
    }
    return formatInfo.PlaneCount;
}
//------------------------------------------------------------------------------------------------
inline UINT METALCalcSubresource( UINT MipSlice, UINT ArraySlice, UINT PlaneSlice, UINT MipLevels, UINT ArraySize )
{ 
    return MipSlice + ArraySlice * MipLevels + PlaneSlice * MipLevels * ArraySize; 
}

//------------------------------------------------------------------------------------------------
struct CD3DX12_RESOURCE_DESC : public METAL_RESOURCE_DESC
{
    CD3DX12_RESOURCE_DESC() = default;
    explicit CD3DX12_RESOURCE_DESC( const METAL_RESOURCE_DESC& o ) :
        METAL_RESOURCE_DESC( o )
    {}
    CD3DX12_RESOURCE_DESC( 
        METAL_RESOURCE_DIMENSION dimension,
        UINT64 alignment,
        UINT64 width,
        UINT height,
        UINT16 depthOrArraySize,
        UINT16 mipLevels,
        DXGI_FORMAT format,
        UINT sampleCount,
        UINT sampleQuality,
        METAL_TEXTURE_LAYOUT layout,
        METAL_RESOURCE_FLAGS flags )
    {
        Dimension = dimension;
        Alignment = alignment;
        Width = width;
        Height = height;
        DepthOrArraySize = depthOrArraySize;
        MipLevels = mipLevels;
        Format = format;
        SampleDesc.Count = sampleCount;
        SampleDesc.Quality = sampleQuality;
        Layout = layout;
        Flags = flags;
    }
    static inline CD3DX12_RESOURCE_DESC Buffer( 
        const METAL_RESOURCE_ALLOCATION_INFO& resAllocInfo,
        METAL_RESOURCE_FLAGS flags = METAL_RESOURCE_FLAG_NONE )
    {
        return CD3DX12_RESOURCE_DESC( METAL_RESOURCE_DIMENSION_BUFFER, resAllocInfo.Alignment, resAllocInfo.SizeInBytes, 
            1, 1, 1, DXGI_FORMAT_UNKNOWN, 1, 0, METAL_TEXTURE_LAYOUT_ROW_MAJOR, flags );
    }
    static inline CD3DX12_RESOURCE_DESC Buffer( 
        UINT64 width,
        METAL_RESOURCE_FLAGS flags = METAL_RESOURCE_FLAG_NONE,
        UINT64 alignment = 0 )
    {
        return CD3DX12_RESOURCE_DESC( METAL_RESOURCE_DIMENSION_BUFFER, alignment, width, 1, 1, 1, 
            DXGI_FORMAT_UNKNOWN, 1, 0, METAL_TEXTURE_LAYOUT_ROW_MAJOR, flags );
    }
    static inline CD3DX12_RESOURCE_DESC Tex1D( 
        DXGI_FORMAT format,
        UINT64 width,
        UINT16 arraySize = 1,
        UINT16 mipLevels = 0,
        METAL_RESOURCE_FLAGS flags = METAL_RESOURCE_FLAG_NONE,
        METAL_TEXTURE_LAYOUT layout = METAL_TEXTURE_LAYOUT_UNKNOWN,
        UINT64 alignment = 0 )
    {
        return CD3DX12_RESOURCE_DESC( METAL_RESOURCE_DIMENSION_TEXTURE1D, alignment, width, 1, arraySize, 
            mipLevels, format, 1, 0, layout, flags );
    }
    static inline CD3DX12_RESOURCE_DESC Tex2D( 
        DXGI_FORMAT format,
        UINT64 width,
        UINT height,
        UINT16 arraySize = 1,
        UINT16 mipLevels = 0,
        UINT sampleCount = 1,
        UINT sampleQuality = 0,
        METAL_RESOURCE_FLAGS flags = METAL_RESOURCE_FLAG_NONE,
        METAL_TEXTURE_LAYOUT layout = METAL_TEXTURE_LAYOUT_UNKNOWN,
        UINT64 alignment = 0 )
    {
        return CD3DX12_RESOURCE_DESC( METAL_RESOURCE_DIMENSION_TEXTURE2D, alignment, width, height, arraySize, 
            mipLevels, format, sampleCount, sampleQuality, layout, flags );
    }
    static inline CD3DX12_RESOURCE_DESC Tex3D( 
        DXGI_FORMAT format,
        UINT64 width,
        UINT height,
        UINT16 depth,
        UINT16 mipLevels = 0,
        METAL_RESOURCE_FLAGS flags = METAL_RESOURCE_FLAG_NONE,
        METAL_TEXTURE_LAYOUT layout = METAL_TEXTURE_LAYOUT_UNKNOWN,
        UINT64 alignment = 0 )
    {
        return CD3DX12_RESOURCE_DESC( METAL_RESOURCE_DIMENSION_TEXTURE3D, alignment, width, height, depth, 
            mipLevels, format, 1, 0, layout, flags );
    }
    inline UINT16 Depth() const
    { return (Dimension == METAL_RESOURCE_DIMENSION_TEXTURE3D ? DepthOrArraySize : 1); }
    inline UINT16 ArraySize() const
    { return (Dimension != METAL_RESOURCE_DIMENSION_TEXTURE3D ? DepthOrArraySize : 1); }
    inline UINT8 PlaneCount(_In_ IMETALDevice* pDevice) const
    { return METALGetFormatPlaneCount(pDevice, Format); }
    inline UINT Subresources(_In_ IMETALDevice* pDevice) const
    { return MipLevels * ArraySize() * PlaneCount(pDevice); }
    inline UINT CalcSubresource(UINT MipSlice, UINT ArraySlice, UINT PlaneSlice)
    { return METALCalcSubresource(MipSlice, ArraySlice, PlaneSlice, MipLevels, ArraySize()); }
};


struct CD3DX12_SHADER_BYTECODE : public METAL_SHADER_BYTECODE
{
    CD3DX12_SHADER_BYTECODE() = default;
    explicit CD3DX12_SHADER_BYTECODE(const METAL_SHADER_BYTECODE &o) :
        METAL_SHADER_BYTECODE(o)
    {}
    CD3DX12_SHADER_BYTECODE(
        _In_ ID3DBlob* pShaderBlob )
    {
        pShaderBytecode = pShaderBlob->GetBufferPointer();
        BytecodeLength = pShaderBlob->GetBufferSize();
    }
    CD3DX12_SHADER_BYTECODE(
        const void* _pShaderBytecode,
        SIZE_T bytecodeLength )
    {
        pShaderBytecode = _pShaderBytecode;
        BytecodeLength = bytecodeLength;
    }
};
//------------------------------------------------------------------------------------------------
struct CD3DX12_RASTERIZER_DESC : public METAL_RASTERIZER_DESC
{
    CD3DX12_RASTERIZER_DESC() = default;
    explicit CD3DX12_RASTERIZER_DESC( const METAL_RASTERIZER_DESC& o ) :
        METAL_RASTERIZER_DESC( o )
    {}
    explicit CD3DX12_RASTERIZER_DESC( CD3DX12_DEFAULT )
    {
        FillMode = METAL_FILL_MODE_SOLID;
        CullMode = METAL_CULL_MODE_BACK;
        FrontCounterClockwise = FALSE;
        DepthBias = METAL_DEFAULT_DEPTH_BIAS;
        DepthBiasClamp = METAL_DEFAULT_DEPTH_BIAS_CLAMP;
        SlopeScaledDepthBias = METAL_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
        DepthClipEnable = TRUE;
        MultisampleEnable = FALSE;
        AntialiasedLineEnable = FALSE;
        ForcedSampleCount = 0;
        ConservativeRaster = METAL_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    }
    explicit CD3DX12_RASTERIZER_DESC(
        METAL_FILL_MODE fillMode,
        METAL_CULL_MODE cullMode,
        BOOL frontCounterClockwise,
        INT depthBias,
        FLOAT depthBiasClamp,
        FLOAT slopeScaledDepthBias,
        BOOL depthClipEnable,
        BOOL multisampleEnable,
        BOOL antialiasedLineEnable, 
        UINT forcedSampleCount, 
        METAL_CONSERVATIVE_RASTERIZATION_MODE conservativeRaster)
    {
        FillMode = fillMode;
        CullMode = cullMode;
        FrontCounterClockwise = frontCounterClockwise;
        DepthBias = depthBias;
        DepthBiasClamp = depthBiasClamp;
        SlopeScaledDepthBias = slopeScaledDepthBias;
        DepthClipEnable = depthClipEnable;
        MultisampleEnable = multisampleEnable;
        AntialiasedLineEnable = antialiasedLineEnable;
        ForcedSampleCount = forcedSampleCount;
        ConservativeRaster = conservativeRaster;
    }
};

//------------------------------------------------------------------------------------------------
struct CD3DX12_BLEND_DESC : public METAL_BLEND_DESC
{
    CD3DX12_BLEND_DESC() = default;
    explicit CD3DX12_BLEND_DESC( const METAL_BLEND_DESC& o ) :
        METAL_BLEND_DESC( o )
    {}
    explicit CD3DX12_BLEND_DESC( CD3DX12_DEFAULT )
    {
        AlphaToCoverageEnable = FALSE;
        IndependentBlendEnable = FALSE;
        const METAL_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlend =
        {
            FALSE,FALSE,
            METAL_BLEND_ONE, METAL_BLEND_ZERO, METAL_BLEND_OP_ADD,
            METAL_BLEND_ONE, METAL_BLEND_ZERO, METAL_BLEND_OP_ADD,
            METAL_LOGIC_OP_NOOP,
            METAL_COLOR_WRITE_ENABLE_ALL,
        };
        for (UINT i = 0; i < METAL_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
            RenderTarget[ i ] = defaultRenderTargetBlend;
    }
};
//------------------------------------------------------------------------------------------------
struct CD3DX12_ROOT_SIGNATURE_DESC : public METAL_ROOT_SIGNATURE_DESC
{
    CD3DX12_ROOT_SIGNATURE_DESC() = default;
    explicit CD3DX12_ROOT_SIGNATURE_DESC(const METAL_ROOT_SIGNATURE_DESC &o) :
        METAL_ROOT_SIGNATURE_DESC(o)
    {}
    CD3DX12_ROOT_SIGNATURE_DESC(
        UINT numParameters,
        _In_reads_opt_(numParameters) const METAL_ROOT_PARAMETER* _pParameters,
        UINT numStaticSamplers = 0,
        _In_reads_opt_(numStaticSamplers) const METAL_STATIC_SAMPLER_DESC* _pStaticSamplers = nullptr,
        METAL_ROOT_SIGNATURE_FLAGS flags = METAL_ROOT_SIGNATURE_FLAG_NONE)
    {
        Init(numParameters, _pParameters, numStaticSamplers, _pStaticSamplers, flags);
    }
    CD3DX12_ROOT_SIGNATURE_DESC(CD3DX12_DEFAULT)
    {
        Init(0, nullptr, 0, nullptr, METAL_ROOT_SIGNATURE_FLAG_NONE);
    }
    
    inline void Init(
        UINT numParameters,
        _In_reads_opt_(numParameters) const METAL_ROOT_PARAMETER* _pParameters,
        UINT numStaticSamplers = 0,
        _In_reads_opt_(numStaticSamplers) const METAL_STATIC_SAMPLER_DESC* _pStaticSamplers = nullptr,
        METAL_ROOT_SIGNATURE_FLAGS flags = METAL_ROOT_SIGNATURE_FLAG_NONE)
    {
        Init(*this, numParameters, _pParameters, numStaticSamplers, _pStaticSamplers, flags);
    }

    static inline void Init(
        _Out_ METAL_ROOT_SIGNATURE_DESC &desc,
        UINT numParameters,
        _In_reads_opt_(numParameters) const METAL_ROOT_PARAMETER* _pParameters,
        UINT numStaticSamplers = 0,
        _In_reads_opt_(numStaticSamplers) const METAL_STATIC_SAMPLER_DESC* _pStaticSamplers = nullptr,
        METAL_ROOT_SIGNATURE_FLAGS flags = METAL_ROOT_SIGNATURE_FLAG_NONE)
    {
        desc.NumParameters = numParameters;
        desc.pParameters = _pParameters;
        desc.NumStaticSamplers = numStaticSamplers;
        desc.pStaticSamplers = _pStaticSamplers;
        desc.Flags = flags;
    }
};

struct CD3DX12_RESOURCE_BARRIER : public METAL_RESOURCE_BARRIER
{
    CD3DX12_RESOURCE_BARRIER() = default;
    explicit CD3DX12_RESOURCE_BARRIER(const METAL_RESOURCE_BARRIER &o) :
        METAL_RESOURCE_BARRIER(o)
    {}
    static inline CD3DX12_RESOURCE_BARRIER Transition(
        _In_ IMETALResource* pResource,
        METAL_RESOURCE_STATES stateBefore,
        METAL_RESOURCE_STATES stateAfter,
        UINT subresource = METAL_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        METAL_RESOURCE_BARRIER_FLAGS flags = METAL_RESOURCE_BARRIER_FLAG_NONE)
    {
        CD3DX12_RESOURCE_BARRIER result = {};
        METAL_RESOURCE_BARRIER &barrier = result;
        result.Type = METAL_RESOURCE_BARRIER_TYPE_TRANSITION;
        result.Flags = flags;
        barrier.Transition.pResource = pResource;
        barrier.Transition.StateBefore = stateBefore;
        barrier.Transition.StateAfter = stateAfter;
        barrier.Transition.Subresource = subresource;
        return result;
    }
    static inline CD3DX12_RESOURCE_BARRIER Aliasing(
        _In_ IMETALResource* pResourceBefore,
        _In_ IMETALResource* pResourceAfter)
    {
        CD3DX12_RESOURCE_BARRIER result = {};
        METAL_RESOURCE_BARRIER &barrier = result;
        result.Type = METAL_RESOURCE_BARRIER_TYPE_ALIASING;
        barrier.Aliasing.pResourceBefore = pResourceBefore;
        barrier.Aliasing.pResourceAfter = pResourceAfter;
        return result;
    }
    static inline CD3DX12_RESOURCE_BARRIER UAV(
        _In_ IMETALResource* pResource)
    {
        CD3DX12_RESOURCE_BARRIER result = {};
        METAL_RESOURCE_BARRIER &barrier = result;
        result.Type = METAL_RESOURCE_BARRIER_TYPE_UAV;
        barrier.UAV.pResource = pResource;
        return result;
    }
};*/