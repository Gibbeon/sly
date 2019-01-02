#include "sly/d3d12/gfx/commandlist.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/convert.h"
#include "sly/d3d12/dxh.h"

using namespace sly::gfx;

D3D12CommandListImpl::D3D12CommandListImpl(D3D12DeviceImpl& device) : _device(&device), _renderState(NULL) {

}

void D3D12CommandListImpl::init(CommandListDesc& desc) {
    getID3D12Device().CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, reinterpret_cast<void**>(&_allocator));
    getID3D12Device().CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,_allocator, NULL, IID_ID3D12CommandList, reinterpret_cast<void**>(&_list));
    _list->Close();
}

void D3D12CommandListImpl::begin() {
    _allocator->Reset();
    _list->Reset(_allocator, _renderState == nullptr ? nullptr : &_renderState->getID3D12PipelineState()); // need to see if we should have pipeline state be here 
}

void D3D12CommandListImpl::end() {
    
    // I think this should be done inside the render target itself somehow?
    // Indicate that the back buffer will now be used to present.
    _list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(&_target->getID3D12Resource(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
    _list->Close();
}

void D3D12CommandListImpl::setRenderTarget(IRenderTarget& target) {
    _target = reinterpret_cast<D3D12RenderTargetImpl*>(&target);
            // Indicate that the back buffer will be used as a render target.
    _list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(&_target->getID3D12Resource(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
    
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
    rtvHandle.ptr = _target->getBufferLocation();

    _list->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
}

void D3D12CommandListImpl::setRenderState(IRenderState& state) {
    _renderState = reinterpret_cast<D3D12RenderStateImpl*>(&state);
    _list->SetPipelineState(&_renderState->getID3D12PipelineState());
}

void D3D12CommandListImpl::setViewport(Viewport& viewport) {
    _list->RSSetViewports(1, &D3D12_VIEWPORT_CAST(viewport));
}

void D3D12CommandListImpl::setScissorRect(sly::rect_t<long> rect) {
    _list->RSSetScissorRects(1, &D3D12_RECT_CAST(rect));
}

void D3D12CommandListImpl::setVertexBuffer(IVertexBuffer& buffer) {    
    _list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    D3D12_VERTEX_BUFFER_VIEW view;

    view.BufferLocation = buffer.getBufferLocation();    
    view.SizeInBytes = (UINT)buffer.getSizeInBytes();    
    view.StrideInBytes = (UINT)buffer.getStrideInBytes();

    _list->IASetVertexBuffers(0, 1, &view);
}
            
void D3D12CommandListImpl::clear(color_t<> color) {
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
    rtvHandle.ptr = _target->getBufferLocation();

    const float clearColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    _list->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}

void D3D12CommandListImpl::draw(size_t a, size_t b, size_t c, size_t d) {
    _list->DrawInstanced((UINT)a, (UINT)b, (UINT)c, (UINT)d);
}

/* #include "te/d3d12/commandlist.h"
#include "te/d3d12/vertexbuffer.h"
#include "te/d3d12/device.h"
#include "te/d3d12/window.h"
#include "te/d3d12/dxh.h"

using namespace te;

D3D12CommandList::D3D12CommandList(D3D12Device* device, ID3D12GraphicsCommandList* list, ID3D12CommandAllocator* allocator) : 
    _list(list),
    _allocator(allocator),
    _device(device) {
        InitRootSignature();
        InitPipelineState();
    }

bool_t D3D12CommandList::InitRootSignature() {
    CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
    ThrowIfFailed(_device->GetID3DDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<void**>(&_rootSignature)));
 return true; 
}

bool_t D3D12CommandList::InitPipelineState() {
    ID3DBlob* vertexShader;
    ID3DBlob* pixelShader;

    #if defined(_DEBUG)
            // Enable better shader debugging with the graphics debugging tools.
            UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    #else
            UINT compileFlags = 0;
    #endif

    ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
    ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

    // Define the vertex input layout.
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    // Describe and create the graphics pipeline state object (PSO).
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    psoDesc.pRootSignature = _rootSignature;
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    ThrowIfFailed(_device->GetID3DDevice()->CreateGraphicsPipelineState(&psoDesc, IID_ID3D12PipelineState, reinterpret_cast<void**>(&_pipelineState)));
     return true; 
}

bool_t D3D12CommandList::Draw(void*<IGfxVertexBuffer> buffer, void*<IGfxWindow> window)
{
    D3D12Window* result = reinterpret_cast<D3D12Window*>(window.ptr());
    Draw(buffer, result->GetActiveRenderTarget(), result->GetActiveHandle());
    return true;
}

bool_t D3D12CommandList::Draw(void*<IGfxVertexBuffer> buffer, ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle) {
     // Command list allocators can only be reset when the associated 
    // command lists have finished execution on the GPU; apps should use 
    // fences to determine GPU execution progress.
    ThrowIfFailed(_allocator->Reset());

    // However, when ExecuteCommandList() is called on a particular command 
    // list, that command list can then be reset at any time and must be before 
    // re-recording.
    ThrowIfFailed(_list->Reset(_allocator, _pipelineState)); // probably need a pipeline state here that's not NULL

    CD3DX12_VIEWPORT _viewport(0.0f, 0.0f, static_cast<float>(1024), static_cast<float>(768));
    CD3DX12_RECT _scissorRect(0, 0, static_cast<LONG>(1024), static_cast<LONG>(768));

    // Set necessary state.
    _list->SetGraphicsRootSignature(_rootSignature);
    _list->RSSetViewports(1, &_viewport);
    _list->RSSetScissorRects(1, &_scissorRect);

    // Indicate that the back buffer will be used as a render target.
    _list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(target, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

    // so the descriptor is on the heap and we need to tell it where that is
    // passing this in for now
    //D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    //rtvHandle.ptr += INT64(m_frameIndex) * UINT64(m_rtvDescriptorSize);

    _list->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

    // Record commands.
    const float clearColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    _list->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    _list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _list->IASetVertexBuffers(0, 1, reinterpret_cast<D3D12VertexBuffer*>(buffer.ptr())->GetVertexBufferView());
    _list->DrawInstanced(3, 1, 0, 0);

    // Indicate that the back buffer will now be used to present.
    _list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(target, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

    ThrowIfFailed(_list->Close());
     return true; 
}

bool_t D3D12CommandList::End() {
    //ThrowIfFailed(_allocator->Reset());

    // However, when ExecuteCommandList() is called on a particular command 
    // list, that command list can then be reset at any time and must be before 
    // re-recording.
    //ThrowIfFailed(_list->Reset(_allocator, _pipelineState));

    return true;
}

 */