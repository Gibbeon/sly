#include <windows.h>
#include "sly.h"
#include "sly/application.h"
#include "sly/gfx.h"

#include <stdio.h>

struct Vec3 {
    float x, y, z;
};

struct Vertex
{
    Vec3 position;
    sly::gfx::color_t color;
};

size_t LoadFromFile(char* file, vptr_t* buffer) {
    FILE* fp;
    fopen_s (&fp, file, "r");
    fseek(fp, 0L, SEEK_END);
    size_t result = ftell(fp);
    rewind(fp); 
    (*buffer) = malloc(result);
    memset(*buffer, 0, result);
    fread((*buffer), result, 1, fp);
    fclose(fp);
    return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
{   
    // initialize the platform and configuration
    sly::Platform::initialize();

    // builder patterns are designed to pass sets of variables into the underlying systems
    sly::ApplicationBuilder applicationBuilder;
    sly::IApplication* application = nullptr;
    sly::Platform::createApplication(&application, applicationBuilder.build());
    
    sly::gfx::RenderSystemBuilder rsBuilder;
    sly::gfx::IRenderSystem* renderSystem = nullptr;
    sly::Platform::createRenderSystem(&renderSystem, rsBuilder.build());

    // can specify which adapter you use, or which rendering system to use if more than one is present
    sly::gfx::DeviceBuilder rdBuilder;
    sly::gfx::IDevice* renderDevice = nullptr;
    renderSystem->createDevice(&renderDevice, rdBuilder.build());

    sly::gfx::WindowBuilder winBuilder;
    sly::gfx::IWindow* window = nullptr;
    //winBuilder.SetBounds(Rect(0, 0, 1024, 768))
    //            .SetColorDepth(32)
    //            .SetBufferCount(2)
    //            .SetFullscreen(false);

    // this will come with a swapchain and a command queue
    renderDevice->createWindow(&window, winBuilder.build());

   
/*     sly::gfx::CommandListBuilder rclBuilder;
    sly::gfx::ICommandList* list = nullptr;
    renderDevice->createCommandList(&list, rclBuilder.build()); */
   
    //D3D11_BUFFER_DESC bufferDesc;
    //bufferDesc.Usage            = D3D11_USAGE_DEFAULT;
    //bufferDesc.ByteWidth        = sizeof( SimpleVertexCombined ) * 3;
    //bufferDesc.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
    //bufferDesc.CPUAccessFlags   = 0;
    //bufferDesc.MiscFlags        = 0;
/*     
    Vertex triangleVertices[] =
    {
        { { 0.0f, 0.25f * (1024/768.0f), 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { 0.25f, -0.25f * (1024/768.0f), 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { -0.25f, -0.25f * (1024/768.0f), 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };  *///this is the initial data

    // Fill in the subresource data.
    //D3D11_SUBRESOURCE_DATA InitData;
    //InitData.pSysMem = verticesCombo;
    //InitData.SysMemPitch = 0;
    //InitData.SysMemSlicePitch = 0;

    // Define the vertex input layout.
    //D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    //{
    //    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    //    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    //};

/*     sly::gfx::InputElementBuilder posBuilder1;
    posBuilder1.setSemanticName("POSITION")
        .setFormat(sly::gfx::eDataFormat_R32G32B32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex);

    sly::gfx::InputElementBuilder posBuilder2;
    posBuilder2.setSemanticName("COLOR")
        .setFormat(sly::gfx::eDataFormat_R32G32B32A32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex)
        .setOffset(12);

    sly::gfx::VertexBufferBuilder vbBuilder;
    vbBuilder.setData(triangleVertices, 3, sizeof(Vertex));

    sly::gfx::IVertexBuffer* vertexBuffer = nullptr;
    renderDevice->createVertexBuffer(&vertexBuffer, vbBuilder.build()); */

/*    sly::gfx::DataBufferBuilder ibBuilder;
    sly::gfx::IDataBuffer* indexBuffer = nullptr;
    renderDevice->createDataBuffer(&indexBuffer, ibBuilder.Build());
*/
/*     sly::gfx::TextureBuilder txtBuilder;
    //D3D11_TEXTURE2D_DESC desc;
    //desc.Width = 256;
    //desc.Height = 256;
    //desc.MipLevels = desc.ArraySize = 1;
    //desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //desc.SampleDesc.Count = 1;
    //desc.Usage = D3D11_USAGE_DYNAMIC;
    //desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    //desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //desc.MiscFlags = 0;
    sly::gfx::ITexture* texture = nullptr;
    renderDevice->createTexture(&texture, txtBuilder.Build()); */


/* HRESULT D3DCompile(
  LPCVOID                pSrcData,
  SIZE_T                 SrcDataSize,
  LPCSTR                 pSourceName,
  const D3D_SHADER_MACRO *pDefines,
  ID3DInclude            *pInclude,
  LPCSTR                 pEntrypoint,
  LPCSTR                 pTarget,
  UINT                   Flags1,
  UINT                   Flags2,
  ID3DBlob               **ppCode,
  ID3DBlob               **ppErrorMsgs
); */
//     ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
/*     vptr_t vsbuf;
    size_t vssize;
    vssize = LoadFromFile("c:\\shaders.hlsl", &vsbuf);
    
    sly::gfx::ShaderBuilder vsspBuilder;
    vsspBuilder.setData(vsbuf, vssize)
                .setEntryPoint("VSMain")
                .setName("shaders")
                .setTarget("vs_5_0");

    sly::gfx::IShader* vsshader = nullptr;
    renderDevice->createShader(&vsshader, vsspBuilder.build()); */

//     ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));
/*     sly::gfx::ShaderBuilder psspBuilder;
    psspBuilder.setData(vsbuf, vssize)
                .setEntryPoint("PSMain")
                .setName("shaders")
                .setTarget("ps_5_0");

    sly::gfx::IShader* psshader = nullptr;
    renderDevice->createShader(&psshader, psspBuilder.build()); */

    //D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    //psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    //psoDesc.pRootSignature = _rootSignature;
    //psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
    //psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
    //psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    //psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    //psoDesc.DepthStencilState.DepthEnable = FALSE;
    //psoDesc.DepthStencilState.StencilEnable = FALSE;
    //psoDesc.SampleMask = UINT_MAX;
    //psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    //psoDesc.NumRenderTargets = 1;
    //psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    //psoDesc.SampleDesc.Count = 1;

/*     sly::gfx::RenderStateBuilder rstBuilder;
    rstBuilder
        .setVSShader(*vsshader)
        .setPSShader(*psshader)
        //.setRasterizerState(CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT))
        //.setBlendState(CD3DX12_BLEND_DESC(D3D12_DEFAULT))
        //.setDepthStencilState(false, false)
        .setSampleMax(UINT_MAX)
        .setPrimitiveType(sly::gfx::ePrimativeType_Triangle)
        .setNumberRenderTargets(1)
        .setRTVFormats(0, sly::gfx::eDataFormat_R8G8B8A8_UNORM)
        .setSampleDesc(1)
        .addInputElementDesriptor(posBuilder1.build())
        .addInputElementDesriptor(posBuilder2.build());

    sly::gfx::IRenderState* rsState = nullptr;
    renderDevice->createRenderState(&rsState, rstBuilder.build());
 */
/* // Set necessary state.
    m_viewport(0.0f, 0.0f, static_cast<float>(1024), static_cast<float>(768)),
    m_scissorRect(0, 0, static_cast<LONG>(1024), static_cast<LONG>(768))

    m_commandList->SetGraphicsRootSignature(m_rootSignature);
    m_commandList->RSSetViewports(1, &m_viewport);
    m_commandList->RSSetScissorRects(1, &m_scissorRect);

    // Indicate that the back buffer will be used as a render target.
    m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

    //CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += INT64(m_frameIndex) * UINT64(m_rtvDescriptorSize);

    m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

    // Record commands.
    const float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
    m_commandList->DrawInstanced(3, 1, 0, 0);

    // Indicate that the back buffer will now be used to present.
    m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

    ThrowIfFailed(m_commandList->Close());
 */
    sly::gfx::Viewport viewport(0, 0, 1024, 768);
    sly::rect_t scissorRect(0, 0, 1024, 768);
    sly::gfx::color_t clearColor(.4f, .4f, .4f, 1.0f);
     
    while(application->isRunning())
    {
 /*        list->begin();
        vertexBuffer->write(triangleVertices, sizeof(triangleVertices), sizeof(Vertex));
        list->setRenderState(*rsState);

        list->setRenderTarget(window->getBackBuffer());

        list->setViewport(viewport);    
        list->setScissorRect(scissorRect);
        list->clear(clearColor);
        list->setVertexBuffer(*vertexBuffer);
        list->draw(3, 1, 0, 0);
        list->end(); */


        application->processMessages();
        window->processMessages();
        
        // read input state
        // read network state
        // update scenes
        //window->getDirectCommandQueue().executeCommandList(list);
        window->swapBuffers();
    }

    


   





























  /*   // stack or not to stack, this is the question
    te::Application app;
    
    //should we follow the builder pattern here as well?
    ENSURE(app.Init(hInstance, pszArgs), "Failed to initialize platform");

    te::GfxSystemBuilder gfxSystemBuilder;

    // is there really a difference between a system and a device?
    // which is the api? device?
    // how would you support d3d12 and d3d11 and opengl4 renderer selection at load time?

    // how are we going to set up app as a memory manager for allocations?

    // should I support NULL/EMPTY desc
    te::IGfxSystem* gfx = nullptr;
    ENSURE(app.CreateGfxSystem(&gfx, gfxSystemBuilder.Build()), "Failed to create GfxSystem");

    te::GfxDeviceBuilder gfxDeviceBuilder;
    te::IGfxDevice* device = nullptr;
    ENSURE(gfx->CreateDevice(&device, gfxDeviceBuilder.Build()), "Failed to create GfxSystem");
            
    te::IGfxWindow* window = nullptr;
    te::WindowBuilder windowDesc;
    windowDesc.SetBounds(te::RECT(0, 0, 1024, 768))
            .SetColorDepth(32)
            .SetBufferCount(2);

    // one device multiple windows? each window would have it's own swapchain and the device would render to it seperatly
    ENSURE(device->CreateGfxWindow(&window, windowDesc.Build()), "Failed to create window");

    // windows need to always be hidden until the main loop beings
    //window->SetVisible(FALSE);

    //te::GfxCommandQueueBuilder queuebufferDesc;

    te::IGfxCommandQueue* queue;
    //ENSURE(device->CreateGfxCommandQueue(&queue, queuebufferDesc.Build()), "");

    // why didn't this work to have multiple queues per window
    // something to do with rendering to the swap chain and failing on present?
    queue = window->GetCommandQueue();

    te::GfxCommandListBuilder bufferDesc;

    te::IGfxCommandList* commands;
    ENSURE(device->CreateGfxCommandList(&commands, bufferDesc.Build()), "");

    // need to add the data required for vertex stride info
    te::GfxVertexBufferBuilder vertexBufferDesc;

    // need to generize buffers and streams here
    te::IGfxVertexBuffer* vertexbuffer;
    ENSURE(device->CreateVertexBuffer(&vertexbuffer, vertexBufferDesc.Build()), "");

    //vertexbuffer->Write(0, 0, 0);


    while(app.IsRunning())
    {
        // surely I don't need to write commands each frame, just execute the queue again
        // does closing the window actually close things down
        //commands->Begin();
        vertexbuffer->Write(0, 0, 0);
        commands->Draw(vertexbuffer, window);

        queue->ExecuteCommandList(commands);
        
        window->ProcessMessages();
        window->SwapBuffers();

        //commands->End();
    }

    // omg memory leak city */
}
