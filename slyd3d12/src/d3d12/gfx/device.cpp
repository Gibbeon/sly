#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/commandlist.h"
#include "sly/d3d12/gfx/rendercontext.h"
#include "sly/d3d12/gfx/vertexbuffer.h"
#include "sly/d3d12/gfx/indexbuffer.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/texture.h"
#include "sly/win32/os/rendercontext.h"

using namespace sly::gfx;

D3D12DeviceImpl::D3D12DeviceImpl(IRenderSystem& system) : _system(&system)
{

}

void D3D12DeviceImpl::init(DeviceDesc& desc) 
{
    UINT dxgiFactoryFlags = 0;

    #ifdef _DEBUG
    {
        ID3D12Debug* debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_ID3D12Debug, reinterpret_cast<vptr_t*>(&debugController))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
    #endif

    CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory4, reinterpret_cast<vptr_t*>(&_factory));

    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != _factory->EnumAdapters1(adapterIndex, &_adapter); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        _adapter->GetDesc1(&desc);

        if (SUCCEEDED(D3D12CreateDevice(_adapter, D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, reinterpret_cast<vptr_t*>(&_device))))
        {
            break;
        }
    }
}

void D3D12DeviceImpl::createWindow(IRenderContext** ppWindow, RenderContextDesc& desc) {
    (*ppWindow) = new D3D12RenderContextImpl(*this, *(new sly::os::Win32Window(1024,768,"Hi!")));
    (*ppWindow)->init(desc);
}

void D3D12DeviceImpl::createCommandQueue(ICommandQueue** queue, CommandQueueDesc& desc) {
    (*queue) = new D3D12CommandQueueImpl(*this);
    (*queue)->init(desc);
}

void D3D12DeviceImpl::createCommandList(ICommandList** ppWindow, CommandListDesc& desc) {
    (*ppWindow) = new D3D12CommandListImpl(*this);
    (*ppWindow)->init(desc);
}

void D3D12DeviceImpl::createRenderState(IRenderState** ppWindow, RenderStateDesc& desc) {
    (*ppWindow) = new D3D12RenderStateImpl(*this);
    (*ppWindow)->init(desc);
}

void D3D12DeviceImpl::createShader(IShader** ppWindow, ShaderDesc& desc) {
    (*ppWindow) = new D3D12ShaderImpl(*this);
    (*ppWindow)->init(desc);
}

void D3D12DeviceImpl::createTexture(ITexture** ppWindow, TextureDesc& desc) {}
void D3D12DeviceImpl::createVertexBuffer(IVertexBuffer** ppWindow, VertexBufferDesc& desc) {
    (*ppWindow) = new D3D12VertexBufferImpl(*this);
    (*ppWindow)->init(desc);
}
void D3D12DeviceImpl::createIndexBuffer(IIndexBufer** ppWindow, IndexBufferDesc& desc) {}


// #include "sly/d3d12/gfx/device.h"
// #include "sly/d3d12/dxh.h"
// //#include "sly/d3d12/gfx/commandqueue.h"
// //#include "sly/d3d12/gfx/commandlist.h"
// //#include "sly/d3d12/gfx/vertexbuffer.h"
// #include "sly/d3d12/gfx/rendercontext.h"
// #include "sly/win32/os/rendercontext.h"


// using namespace sly::gfx;

// D3D12Device::D3D12Device(IDXGIFactory4& factory, IDXGIAdapter1& adapter, ID3D12Device& device) :
//     factory_(factory),
//     adapter_(adapter),
//     _device(device) {
    
//     //InitRootSignature();
//     //InitPipelineState();
// }
// /* 
// bool_t D3D12Device::InitRootSignature() {
//     CD3DX12_ROOT_SIGNATURE_DESC rootSignature;
//     rootSignature.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

//     ID3DBlob* signature;
//     ID3DBlob* error;

//     ThrowIfFailed(D3D12SerializeRootSignature(&_rootSignature, D3DROOT_SIGNATURE_VERSION_1, &signature, &error));
//     ThrowIfFailed(_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<vptr_t*>(&_rootSignature)));
//     return true;
// }

// bool_t D3D12Device::InitPipelineState() {
//     ID3DBlob* vertexShader;
//     ID3DBlob* pixelShader;

//     #if defined(_DEBUG)
//             // Enable better shader debugging with the graphics debugging tools.
//             UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//     #else
//             UINT compileFlags = 0;
//     #endif

//     ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
//     ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

//     // Define the vertex input layout.
//     D3D12_INPUT_ELEMENT_DESC inputElements[] =
//     {
//         { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//         { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
//     };

//     // ribe and create the graphics pipeline state object (PSO).
//     D3D12_GRAPHICS_PIPELINE_STATE_DESC pso = {};
//     pso.InputLayout = { inputElements, _countof(inputElements) };
//     pso.pRootSignature = _rootSignature;
//     pso.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
//     pso.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
//     pso.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//     pso.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//     pso.DepthStencilState.DepthEnable = FALSE;
//     pso.DepthStencilState.StencilEnable = FALSE;
//     pso.SampleMask = UINT_MAX;
//     pso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//     pso.NumRenderTargets = 1;
//     pso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//     pso.Sample.Count = 1;

//     ThrowIfFailed(_device->CreateGraphicsPipelineState(&_pso, IIDID3D12PipelineState, reinterpret_cast<vptr_t*>(&_pipelineState)));
//         return true;
// } */

// void D3D12Device::createCommandQueue(ICommandQueue** queue, CommandQueue& desc) {
// /*     // ribe and create the command queue.
//     D3D12_COMMAND_QUEUE_DESC queue = {};
//     queue.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//     queue.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

//     ID3D12CommandQueue* commandQueue = nullptr;
//     ThrowIfFailed(_device->CreateCommandQueue(&_queue, IIDID3D12CommandQueue, reinterpret_cast<vptr_t*>(&commandQueue)));

//     (*queue) = new D3D12CommandQueue(commandQueue, _device);
//     return true; */
// }

// void D3D12Device::createCommandList(ICommandList** list, CommandList& desc) {
//     /* ID3D12CommandAllocator* commandAllocator;
//     ID3D12GraphicsCommandList* commandList;

//     ThrowIfFailed(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, reinterpret_cast<vptr_t*>(&commandAllocator)));

//     ThrowIfFailed(_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, IID_ID3D12CommandList, reinterpret_cast<vptr_t*>(&commandList)));

//     ThrowIfFailed(commandList->Close());

//     (*list) = new D3D12CommandList(this, commandList, commandAllocator);
//     return true; */
// }

// void D3D12Device::createShader(IShader** ppWindow, Shader& desc) {

// }

// void D3D12Device::createTexture(ITexture** ppWindow, Texture& desc) {

// }
 

// void D3D12Device::createDataBuffer(IDataBuffer** buffer, DataBuffer& desc) {
//     // Note: using upload heaps to transfer static data like vert buffers is not 
//     // recommended. Every time the GPU needs it, the upload heap will be marshalled 
//     // over. Please read up on Default Heap usage. An upload heap is used here for 
//     // code simplicity and because there are very few verts to actually transfer.
// /* 
//     ID3D12Resource* vertexBuffer = nullptr;

//     Vertex triangleVertices[] =
//         {
//             { { 0.0f, 0.25f * (1), 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
//             { { 0.25f, -0.25f * 1, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
//             { { -0.25f, -0.25f * 1, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
//         };

//         const UINT vertexBufferSize = sizeof(triangleVertices);

//     ThrowIfFailed(_device->CreateCommittedResource(
//         &_CD3DX12HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//         D3D12_HEAP_FLAG_NONE,
//         &_CD3DX12RESOURCE_DESC::Buffer(vertexBufferSize),
//         D3D12_RESOURCE_STATE_GENERIC_READ,
//         nullptr,
//         IID_ID3D12Resource, 
//         reinterpret_cast<vptr_t*>(&vertexBuffer)));

//     (*buffer) = new D3D12VertexBuffer(vertexBuffer, vertexBufferSize);
//     return true; */
// }

// void D3D12Device::createWindow(IRenderContext** window, Window& desc) {
//     window = new D3D12Window(this, new sly::os::Win32Window(1024, 768,  "Sample Title"));
// }