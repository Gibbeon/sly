#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/d3d12/gfx/commandlist.h"
#include "sly/d3d12/gfx/window.h"
#include "sly/d3d12/gfx/vertexbuffer.h"
#include "sly/d3d12/gfx/indexbuffer.h"
#include "sly/d3d12/gfx/shader.h"
#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/texture.h"
#include "sly/win32/sys/window.h"

using namespace sly::gfx;

D3D12DeviceImpl::D3D12DeviceImpl(ref_t<DeviceDesc> desc) {
    UINT dxgiFactoryFlags = 0;

    #ifdef _DEBUG
    {
        ID3D12Debug* debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_ID3D12Debug, reinterpret_cast<void**>(&debugController))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
    #endif

    CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory4, reinterpret_cast<void**>(&factory_));

    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory_->EnumAdapters1(adapterIndex, &adapter_); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter_->GetDesc1(&desc);

        if (SUCCEEDED(D3D12CreateDevice(adapter_, D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, reinterpret_cast<void**>(&device_))))
        {
            break;
        }
    }
}

void D3D12DeviceImpl::createWindow(out_ptr_t<IWindow> ppWindow, ref_t<WindowDesc> desc) {
    ppWindow = new D3D12WindowImpl(this, new sly::sys::Win32Window(1024,768,"Hi!"));
    ppWindow->init(desc);
}

void D3D12DeviceImpl::createCommandQueue(out_ptr_t<ICommandQueue> queue, ref_t<CommandQueueDesc> desc) {
    queue = new D3D12CommandQueueImpl(this, desc);
}

void D3D12DeviceImpl::createCommandList(out_ptr_t<ICommandList> ppWindow, ref_t<CommandListDesc> desc) {
    ppWindow = new D3D12CommandListImpl(this, desc);
}

void D3D12DeviceImpl::createRenderState(out_ptr_t<IRenderState> ppWindow, ref_t<RenderStateDesc> desc) {
    ppWindow = new D3D12RenderStateImpl(this);
    ppWindow->init(desc);
}

void D3D12DeviceImpl::createShader(out_ptr_t<IShader> ppWindow, ref_t<ShaderDesc> desc) {
    ppWindow = new D3D12ShaderImpl(this);
    ppWindow->init(desc);
}

void D3D12DeviceImpl::createTexture(out_ptr_t<ITexture> ppWindow, ref_t<TextureDesc> desc) {}
void D3D12DeviceImpl::createVertexBuffer(out_ptr_t<IVertexBuffer> ppWindow, ref_t<VertexBufferDesc> desc) {
    ppWindow = new D3D12VertexBufferImpl(this);
    ppWindow->init(desc);
}
void D3D12DeviceImpl::createIndexBuffer(out_ptr_t<IIndexBufer> ppWindow, ref_t<IndexBufferDesc> desc) {}


// #include "sly/d3d12/gfx/device.h"
// #include "sly/d3d12/dxh.h"
// //#include "sly/d3d12/gfx/commandqueue.h"
// //#include "sly/d3d12/gfx/commandlist.h"
// //#include "sly/d3d12/gfx/vertexbuffer.h"
// #include "sly/d3d12/gfx/window.h"
// #include "sly/win32/sys/window.h"


// using namespace sly::gfx;

// D3D12Device::D3D12Device(ref_t<IDXGIFactory4> factory, ref_t<IDXGIAdapter1> adapter, ref_t<ID3D12Device> device) :
//     factory_(factory),
//     adapter_(adapter),
//     device_(device) {
    
//     //InitRootSignature();
//     //InitPipelineState();
// }
// /* 
// bool_t D3D12Device::InitRootSignature() {
//     CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
//     rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

//     ID3DBlob* signature;
//     ID3DBlob* error;

//     ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
//     ThrowIfFailed(_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<void**>(&_rootSignature)));
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
//     D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
//     {
//         { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//         { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
//     };

//     // Describe and create the graphics pipeline state object (PSO).
//     D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
//     psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
//     psoDesc.pRootSignature = _rootSignature;
//     psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
//     psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
//     psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//     psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//     psoDesc.DepthStencilState.DepthEnable = FALSE;
//     psoDesc.DepthStencilState.StencilEnable = FALSE;
//     psoDesc.SampleMask = UINT_MAX;
//     psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//     psoDesc.NumRenderTargets = 1;
//     psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//     psoDesc.SampleDesc.Count = 1;

//     ThrowIfFailed(_device->CreateGraphicsPipelineState(&psoDesc, IID_ID3D12PipelineState, reinterpret_cast<void**>(&_pipelineState)));
//         return true;
// } */

// void D3D12Device::createCommandQueue(out_ptr_t<ICommandQueue> queue, ref_t<CommandQueueDesc> desc) {
// /*     // Describe and create the command queue.
//     D3D12_COMMAND_QUEUE_DESC queueDesc = {};
//     queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//     queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

//     ID3D12CommandQueue* commandQueue = nullptr;
//     ThrowIfFailed(_device->CreateCommandQueue(&queueDesc, IID_ID3D12CommandQueue, reinterpret_cast<void**>(&commandQueue)));

//     (*queue) = new D3D12CommandQueue(commandQueue, _device);
//     return true; */
// }

// void D3D12Device::createCommandList(out_ptr_t<ICommandList> list, ref_t<CommandListDesc> desc) {
//     /* ID3D12CommandAllocator* commandAllocator;
//     ID3D12GraphicsCommandList* commandList;

//     ThrowIfFailed(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, reinterpret_cast<void**>(&commandAllocator)));

//     ThrowIfFailed(_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, IID_ID3D12CommandList, reinterpret_cast<void**>(&commandList)));

//     ThrowIfFailed(commandList->Close());

//     (*list) = new D3D12CommandList(this, commandList, commandAllocator);
//     return true; */
// }

// void D3D12Device::createShader(out_ptr_t<IShader> ppWindow, ref_t<ShaderDesc> desc) {

// }

// void D3D12Device::createTexture(out_ptr_t<ITexture> ppWindow, ref_t<TextureDesc> desc) {

// }
 

// void D3D12Device::createDataBuffer(out_ptr_t<IDataBuffer> buffer, ref_t<DataBufferDesc> desc) {
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
//         &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//         D3D12_HEAP_FLAG_NONE,
//         &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
//         D3D12_RESOURCE_STATE_GENERIC_READ,
//         nullptr,
//         IID_ID3D12Resource, 
//         reinterpret_cast<void**>(&vertexBuffer)));

//     (*buffer) = new D3D12VertexBuffer(vertexBuffer, vertexBufferSize);
//     return true; */
// }

// void D3D12Device::createWindow(out_ptr_t<IWindow> window, ref_t<WindowDesc> desc) {
//     window = new D3D12Window(this, new sly::sys::Win32Window(1024, 768,  "Sample Title"));
// }