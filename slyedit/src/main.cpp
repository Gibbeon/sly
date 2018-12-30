#include <windows.h>
#include "sly.h"
#include "sly/application.h"
#include "sly/gfx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
{   
    // initialize the platform and configuration
    sly::Platform::initialize();

    // builder patterns are designed to pass sets of variables into the underlying systems
    sly::ApplicationBuilder applicationBuilder;
    local_ptr_t<sly::IApplication> application = nullptr;
    sly::Platform::createApplication(application, applicationBuilder.Build());
    
    
    sly::gfx::RenderSystemBuilder rsBuilder;
    local_ptr_t<sly::gfx::IRenderSystem> renderSystem = nullptr;
    sly::Platform::createRenderSystem(renderSystem, rsBuilder.Build());

    /* // can specify which adapter you use, or which rendering system to use if more than one is present
    sly::gfx::DeviceBuilder rdBuilder;
    local_ptr_t<sly::gfx::IDevice> renderDevice = nullptr;
    renderSystem->createDevice(renderDevice, rdBuilder.Build());

    sly::gfx::WindowBuilder winBuilder;
    local_ptr_t<sly::gfx::IWindow> window = nullptr;
    //winBuilder.SetBounds(Rect(0, 0, 1024, 768))
    //            .SetColorDepth(32)
    //            .SetBufferCount(2)
    //            .SetFullscreen(false);

    // this will come with a swapchain and a command queue
    renderDevice->createWindow(window, winBuilder.Build());

    sly::gfx::CommandListBuilder rclBuilder;
    local_ptr_t<sly::gfx::ICommandList> list = nullptr;
    renderDevice->createCommandList(list, rclBuilder.Build());

    sly::gfx::DataBufferBuilder vbBuilder;
    
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
    local_ptr_t<sly::gfx::IDataBuffer> vertexBuffer = nullptr;
    renderDevice->createDataBuffer(&vertexBuffer, vbBuilder.Build());

    sly::gfx::DataBufferBuilder ibBuilder;
    local_ptr_t<sly::gfx::IDataBuffer> indexBuffer = nullptr;
    renderDevice->createDataBuffer(&indexBuffer, ibBuilder.Build());

    sly::gfx::TextureBuilder txtBuilder;
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
    local_ptr_t<sly::gfx::ITexture> texture = nullptr;
    renderDevice->createTexture(&texture, txtBuilder.Build());

    sly::gfx::ShaderBuilder vsspBuilder;
    local_ptr_t<sly::gfx::IShader> vsshader = nullptr;
    renderDevice->createShader(&vsshader, vsspBuilder.Build());

    sly::gfx::ShaderBuilder psspBuilder;
    local_ptr_t<sly::gfx::IShader> psshader = nullptr;
    renderDevice->createShader(&psshader, psspBuilder.Build());

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

    list->begin();
    list->setViewport();
    list->setCamera();
    list->setProjection();
    list->setScissorRect();
    list->setVSShader();
    list->setPSShader();
    list->setVertexBuffer();
    list->setIndexBuffer();
    list->setTexture();
    list->drawIndexed();
    list->end();
 */
    while(application->isRunning())
    {
        //application->processEvents();
        //window->processEvents();
        
        // read input state
        // read network state
        // update scenes
        //sly::Array<sly::gfx::ICommandList> batch((sly::gfx::ICommandList*)list.ptr(), 1);
        //window->getRenderQueue()->executeCommandList(batch);
        //window->swapBuffers();
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
