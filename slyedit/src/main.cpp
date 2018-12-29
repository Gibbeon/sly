#include <windows.h>
#include "sly.h"
#include "sly/application.h"
#include "sly/gfx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
{   
    // initialize the platform and configuration
    // builder patterns are designed to pass sets of variables into the underlying systems
    sly::ApplicationDescBuilder applicationDescBuilder;
    local_ptr_t<sly::IApplication> application = nullptr;
    sly::Platform::CreateApplication(application, applicationDescBuilder.Build());

    sly::Platform::SetApplication(application);
    
    sly::RenderSystemDescBuilder rsDescBuilder;
    local_ptr_t<sly::IRenderSystem> renderSystem = nullptr;
    sly::Platform::CreateRenderSystem(renderSystem, rsDescBuilder.Build());

    sly::Platform::SetRenderSystem(renderSystem);

    // can specify which adapter you use, or which rendering system to use if more than one is present
    sly::RenderDeviceDescBuilder rdDescBuilder;
    local_ptr_t<sly::IRenderDevice> renderDevice = nullptr;
    renderSystem->CreateRenderDevice(renderDevice, rdDescBuilder.Build());

    sly::RenderWindowDescBuilder winDescBuilder;
    sly::IRenderWindow* window = nullptr;
    //winDescBuilder.SetBounds(Rect(0, 0, 1024, 768))
    //            .SetColorDepth(32)
    //            .SetBufferCount(2)
    //            .SetFullscreen(false);

    // this will come with a swapchain and a command queue
    renderDevice->CreateRenderWindow(&window, winDescBuilder.Build());

    sly::RenderCommandListDescBuilder rclBuilder;
    sly::IRenderCommandList* list = nullptr;
    renderDevice->CreateRenderCommandList(&list, rclBuilder.Build());

    sly::RenderBufferDescBuilder vbBuilder;
    
    //D3D11_BUFFER_DESC bufferDesc;
    //bufferDesc.Usage            = D3D11_USAGE_DEFAULT;
    //bufferDesc.ByteWidth        = sizeof( SimpleVertexCombined ) * 3;
    //bufferDesc.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
    //bufferDesc.CPUAccessFlags   = 0;
    //bufferDesc.MiscFlags        = 0;
    
    //Vertex triangleVertices[] =
    //{
    //    { { 0.0f, 0.25f * (m_aspectRatio), 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    //    { { 0.25f, -0.25f * m_aspectRatio, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    //    { { -0.25f, -0.25f * m_aspectRatio, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    //}; this is the initial data

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
    sly::IRenderBuffer* vertexBuffer = nullptr;
    renderDevice->CreateRenderBuffer(&vertexBuffer, vbBuilder.Build());

    sly::RenderBufferDescBuilder ibBuilder;
    sly::IRenderBuffer* indexBuffer = nullptr;
    renderDevice->CreateRenderBuffer(&indexBuffer, ibBuilder.Build());

    sly::RenderTextureDescBuilder txtBuilder;
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
    sly::IRenderTexture* texture = nullptr;
    renderDevice->CreateRenderTexture(&texture, txtBuilder.Build());

    sly::RenderShaderDescBuilder vsspBuilder;
    sly::IRenderShader* vsshader = nullptr;
    renderDevice->CreateRenderShader(&vsshader, vsspBuilder.Build());

    sly::RenderShaderDescBuilder psspBuilder;
    sly::IRenderShader* psshader = nullptr;
    renderDevice->CreateRenderShader(&psshader, psspBuilder.Build());

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

    list->Begin();
    list->SetViewport();
    list->SetCamera();
    list->SetProjection();
    list->SetScissorRect();
    list->SetVSShader();
    list->SetPSShader();
    list->SetVertexBuffer();
    list->SetIndexBuffer();
    list->SetTexture();
    list->DrawIndexed();
    list->End();

    while(application->IsRunning())
    {
        application->ProcessEvents();
        window->ProcessEvents();
        
        // read input state
        // read network state
        // update scenes
        sly::Array<sly::IRenderCommandList*> batch(&list, 1);
        window->GetRenderQueue()->ExecuteCommandList(batch);
        window->SwapBuffers();
    }

    


   





























  /*   // stack or not to stack, this is the question
    te::Application app;
    
    //should we follow the builder pattern here as well?
    ENSURE(app.Init(hInstance, pszArgs), "Failed to initialize platform");

    te::GfxSystemDescBuilder gfxSystemBuilder;

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
