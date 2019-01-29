//#include <windows.h>
#include "sly.h"

#include "sly/os/os.h"
#include "sly/gfx.h"
#include "sly/runtime/serialization/jsonserializer.h"
#include "sly/runtime/serialization/binaryserializer.h"

#include <stdio.h>

template<typename T = void>
struct result_t {
    result_t() : successful(true) {}
    result_t(T value) : retval (value) {}
    
    bool_t successful;
    T retval;

    operator T const & () const noexcept { return retval; }
    operator T       & ()     & noexcept { return retval; }
    operator T      && ()    && noexcept { return std::move(retval); }
};

struct Vec3 {
    float x, y, z;
};

struct Vertex
{
    Vec3 position;
    sly::gfx::color_t color;
};

class Other {
public:
    Other() : _random(0) {

    }

    virtual ~Other() {}

    virtual void setData(u32 value) {
        _random = value;
    }
protected:
    u32 _random;
};

class TestClass : public sly::ISerializable
 {
public:
    _GET_TYPE_INFO();

    TestClass() : _data(0) {

    }

    virtual ~TestClass() {}

    virtual void setData(u32 value) {
        _data = value;
    }
        
    virtual void serialize(sly::ISerializer& data) {
        data.write("_data", _data);
        //sly::BinaryWriter writer(stream);
        //writer.write(_data);
        //writer.write(17);
    }

    virtual void deserialize(sly::IDeserializer& data) {
        //data.read("_data", &_data);
        //sly::BinaryReader reader(stream);
        //_data = reader.read<u32>();
        //u32 test = reader.read<u32>();
    }

protected:
    u32 _data;
};

// desc no registration
/*    sly::IOutputStream* pDataFile;
    sly::Engine::OS().FileSystem().create(&pDataFile, u8"output.dat");
    sly::BinarySerializer serializer(*pDataFile);

    sly::gfx::InputElementBuilder test1;
    test1.setSemanticName("POSITION")
        .setFormat(sly::gfx::eDataFormat_R32G32B32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex);

    sly::TypeInfo type = sly::TypeInfo::get<sly::gfx::InputElementDesc>();
    serializer.write(type, &test1.build(), sizeof(sly::gfx::InputElementDesc));

    pDataFile->close();

    sly::IInputStream* pInputFile;
    sly::Engine::OS().FileSystem().open(&pInputFile, u8"output.dat");

    sly::BinaryDeserializer deserializer(*pInputFile);
    sly::gfx::InputElementDesc desc;
    deserializer.read(&desc, sizeof(sly::gfx::InputElementDesc));

    pInputFile->close();*/
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
#else
int main()
#endif
{   
    // load configuration, plugins, etc
    sly::Engine::init();

    sly::IOutputStream* pDataFile;
    sly::Engine::OS().FileSystem().create(&pDataFile, u8"output.dat");
    sly::JSONSerializer serializer(*pDataFile);

    TestClass data;  
    data.setData(12);

    sly::TypeInfo type = sly::TypeInfo::get<TestClass>();
    serializer.write(type, &data);

    pDataFile->close();

    sly::IInputStream* pInputFile;
    sly::Engine::OS().FileSystem().open(&pInputFile, u8"output.dat");

    sly::TypeActivator activator;
    activator.add<TestClass>();
    sly::JSONDeserializer deserializer(*pInputFile, activator);
    TestClass data2;
    deserializer.read(&data2, sizeof(TestClass));

    pInputFile->close();

    return 0;


    // choosing between multiple render systems?
    sly::gfx::RenderSystemBuilder rsBuilder;
    sly::gfx::IRenderSystem* renderSystem = nullptr;
    sly::Engine::createRenderSystem(&renderSystem);//, rsBuilder.build());

    // create a device
    sly::gfx::DeviceBuilder rdBuilder;
    sly::gfx::IDevice* renderDevice = nullptr;
    renderSystem->createDevice(&renderDevice, rdBuilder.build());

    // create 1 or more windows
    sly::gfx::WindowBuilder winBuilder;
    sly::gfx::IWindow* window = nullptr;
    renderDevice->createWindow(&window, winBuilder.build());

    // create a command list to draw an object
    sly::gfx::CommandListBuilder rclBuilder;
    sly::gfx::ICommandList* list = nullptr;
    renderDevice->createCommandList(&list, rclBuilder.build());
    
    // data
    Vertex* triangleVertices = nullptr;
    sly::IInputStream* pVertexData;
    sly::Engine::OS().FileSystem().open(&pVertexData, u8"vertex.dat");
    size_t vtxsize = pVertexData->getSize();
    
    triangleVertices = (Vertex*)malloc(vtxsize);
    pVertexData->read(triangleVertices, vtxsize);

    sly::gfx::InputElementBuilder posBuilder1;
    posBuilder1.setSemanticName("POSITION")
        .setFormat(sly::gfx::eDataFormat_R32G32B32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex);

    sly::gfx::InputElementBuilder posBuilder2;
    posBuilder2.setSemanticName("COLOR")
        .setFormat(sly::gfx::eDataFormat_R32G32B32A32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex)
        .setOffset(12);

    sly::gfx::VertexBufferBuilder vbBuilder;
    vbBuilder.setData(triangleVertices, vtxsize / sizeof(Vertex), sizeof(Vertex));

    sly::gfx::IVertexBuffer* vertexBuffer = nullptr;
    renderDevice->createVertexBuffer(&vertexBuffer, vbBuilder.build()); 

    //shaders
    sly::IInputStream* pShaderFile;
    sly::Engine::OS().FileSystem().open(&pShaderFile, u8"c:\\shaders.hlsl");

    size_t vssize = pShaderFile->getSize();
    
    char* vsbuf = (char*)malloc(vssize);
    pShaderFile->read(vsbuf, vssize);

    
    sly::gfx::ShaderBuilder vsspBuilder;
    vsspBuilder.setData(vsbuf, vssize)
                .setEntryPoint("VSMain")
                .setName("shaders")
                .setTarget("vs_5_0");

    sly::gfx::IShader* vsshader = nullptr;
    renderDevice->createShader(&vsshader, vsspBuilder.build()); 

     sly::gfx::ShaderBuilder psspBuilder;
    psspBuilder.setData(vsbuf, vssize)
                .setEntryPoint("PSMain")
                .setName("shaders")
                .setTarget("ps_5_0");

    sly::gfx::IShader* psshader = nullptr;
    renderDevice->createShader(&psshader, psspBuilder.build()); 

    // render state
    sly::gfx::RenderStateBuilder rstBuilder;
    rstBuilder
        .setVSShader(*vsshader)
        .setPSShader(*psshader)
        .setSampleMax(UINT_MAX)
        .setPrimitiveType(sly::gfx::ePrimativeType_Triangle)
        .setNumberRenderTargets(1)
        .setRTVFormats(0, sly::gfx::eDataFormat_R8G8B8A8_UNORM)
        .setSampleDesc(1)
        .addInputElementDesriptor(posBuilder1.build())
        .addInputElementDesriptor(posBuilder2.build());

    sly::gfx::IRenderState* rsState = nullptr;
    renderDevice->createRenderState(&rsState, rstBuilder.build());

    // state
    sly::gfx::Viewport viewport(0, 0, 1024, 768);
    sly::rect_t scissorRect(0, 0, 1024, 768);
    sly::gfx::color_t clearColor(.4f, .4f, .4f, 1.0f);   

    while(true)
    {
        // loop
        list->begin();
        list->setRenderState(*rsState);
        list->setRenderTarget(window->getDrawBuffer());
        list->setViewport(viewport);    
        list->setScissorRect(scissorRect);
        list->clear(clearColor);
        list->setVertexBuffer(*vertexBuffer);
        list->draw(3, 1, 0, 0);
        list->end(); 

        //application->processMessages();

        window->processMessages();        
        window->getDirectCommandQueue().executeCommandList(list);
        window->getDirectCommandQueue().flush();
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
    te::WindowBuilder window;
    window.SetBounds(te::RECT(0, 0, 1024, 768))
            .SetColorDepth(32)
            .SetBufferCount(2);

    // one device multiple windows? each window would have it's own swapchain and the device would render to it seperatly
    ENSURE(device->CreateGfxWindow(&window, window.Build()), "Failed to create window");

    // windows need to always be hidden until the main loop beings
    //window->SetVisible(FALSE);

    //te::GfxCommandQueueBuilder queuebuffer;

    te::IGfxCommandQueue* queue;
    //ENSURE(device->CreateGfxCommandQueue(&queue, queuebuffer.Build()), "");

    // why didn't this work to have multiple queues per window
    // something to do with rendering to the swap chain and failing on present?
    queue = window->GetCommandQueue();

    te::GfxCommandListBuilder buffer;

    te::IGfxCommandList* commands;
    ENSURE(device->CreateGfxCommandList(&commands, buffer.Build()), "");

    // need to add the data required for vertex stride info
    te::GfxVertexBufferBuilder vertexBuffer;

    // need to generize buffers and streams here
    te::IGfxVertexBuffer* vertexbuffer;
    ENSURE(device->CreateVertexBuffer(&vertexbuffer, vertexBuffer.Build()), "");

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
