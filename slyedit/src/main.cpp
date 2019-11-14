

#ifdef _WIN32
#include <windows.h>
#endif


#include "sly.h"

#include "sly/os/os.h"
#include "sly/gfx.h"

#include "sly/runtime/serialization/serializer.h"

struct Vec3 {
    float x, y, z;
};

struct Vertex
{
    Vec3 position;
    sly::gfx::color_t color;
};

namespace sly {

    template<size_t N, typename TType = u8>
    struct StackAlloc
    {
        TType buffer[N];
        size_t size = N;

        operator TType* const() { return buffer; } 
    };
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
#else
int main()
#endif
{  
    sly::EngineBuilder engBuilder;
    sly::StackAlloc<4096> buffer;

    engBuilder
        .setSystemMemoryHeap(sly::eSystemMemoryHeap_Default,    sly::MemoryHeapBuilder().setBytes(buffer, buffer.size).setDebug(true).build())
        .setSystemMemoryHeap(sly::eSystemMemoryHeap_Resources,  sly::MemoryHeapBuilder().setSize(1024 * 1024 * 32).setDebug(true).build())
        .setSystemMemoryHeap(sly::eSystemMemoryHeap_Debug,      sly::MemoryHeapBuilder().setSize(1024 * 1024 * 32).setDebug(true).build())
        .setLogLevel(sly::eLogLevel_Info);

    // load configuration, plugins, etc
    sly::Engine::init(engBuilder.build());    

    // choosing between multiple render systems? -- this points to an API d3d12, opengl, etc.
    sly::gfx::IRenderSystem* renderSystem = nullptr;
    sly::Engine::createRenderSystem(&renderSystem, sly::gfx::RenderSystemBuilder().build());

    // create a device context, this managers resources for the render system
    sly::gfx::IDevice* renderDevice = nullptr; // device becomes renderer???
    renderSystem->createDevice(&renderDevice, sly::gfx::DeviceBuilder().build());

    // create window
    sly::gfx::IRenderContext* context = nullptr;
    renderDevice->createRenderContext(&context, sly::gfx::RenderContextBuilder().build());

    // create 1 or more windows
    //renderDevice->setRender(&window, winBuilder.build());

    // create a command list to draw an object 
    sly::gfx::ICommandList* list = nullptr;
    renderDevice->createCommandList(&list, sly::gfx::CommandListBuilder().build());

    sly::gfx::ShaderBuilder psspBuilder;
    sly::gfx::ShaderBuilder vsspBuilder;

    sly::gfx::VertexBufferBuilder vbBuilder;

    sly::gfx::InputElementBuilder posBuilder1;
    posBuilder1.setSemanticName("POSITION")
        .setFormat(sly::gfx::eDataFormat_R32G32B32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex);

    sly::gfx::InputElementBuilder posBuilder2;
    posBuilder2.setSemanticName("COLOR")
        .setFormat(sly::gfx::eDataFormat_R32G32B32A32_FLOAT)
        .setInputScope(sly::gfx::eDataInputClassification_PerVertex)
        .setOffset(12);

    //#define TEST_ASSETREADER 1
    #if !TEST_ASSETREADER
    
        Vertex* triangleVertices = nullptr;
        sly::IInputStream* pVertexData;
        sly::Engine::OS().FileSystem().open(&pVertexData, "vertex.dat");

        size_t vtxsize = pVertexData->getSize();
        
        triangleVertices = (Vertex*)malloc(vtxsize);
        pVertexData->read(triangleVertices, vtxsize);

        vbBuilder.setData(triangleVertices, vtxsize / sizeof(Vertex), sizeof(Vertex));

        //shaders
        sly::IInputStream* pShaderFile;
        sly::Engine::OS().FileSystem().open(&pShaderFile, u8"c:\\shaders.hlsl");

        size_t vssize = pShaderFile->getSize();
        
        char* vsbuf = (char*)malloc(vssize);
        pShaderFile->read(vsbuf, vssize);

        vsspBuilder.setData(vsbuf, vssize)
                    .setEntryPoint("VSMain")
                    .setName("shaders")
                    .setTarget("vs_5_0");


        psspBuilder.setData(vsbuf, vssize)
                    .setEntryPoint("PSMain")
                    .setName("shaders")
                    .setTarget("ps_5_0");
   
    #else
        sly::TypeActivator activator;

        sly::IInputStream* pVertexData;
        sly::Engine::OS().FileSystem().open(&pVertexData, "vertex.json");
        sly::JSONDeserializer vbReader(pVertexData, activator);
        sly::gfx::VertexBufferDesc vbDesc = vbReader.read<sly::gfx::VertexBufferDesc>();
        pVertexData->close();

        vbBuilder.init(vbDesc);

        sly::IInputStream* pShaderData;
        sly::Engine::OS().FileSystem().open(&pShaderData, "shaders.json");
        sly::JSONDeserializer shaderReader(pShaderData, activator);
        sly::gfx::ShaderBuilder vsspDesc = shaderReader.read<sly::gfx::ShaderBuilder>();
        sly::gfx::ShaderBuilder psspDesc = shaderReader.read<sly::gfx::ShaderBuilder>();
        pShaderData->close();

        psspBuilder.init(psspDesc);
        vsspBuilder.init(vsspDesc);
    #endif

    sly::gfx::IVertexBuffer* vertexBuffer = nullptr;
    renderDevice->createVertexBuffer(&vertexBuffer, vbBuilder.build()); 

    sly::gfx::IShader* psshader = nullptr;
    sly::gfx::IShader* vsshader = nullptr;

    renderDevice->createShader(&vsshader, vsspBuilder.build()); 
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
        list->setRenderTarget(context->getDrawBuffer());
        list->setViewport(viewport);    
        list->setScissorRect(scissorRect);
        list->clear(clearColor);
        list->setVertexBuffer(*vertexBuffer);
        list->draw(3, 1, 0, 0);
        list->end(); 

        context->processMessages();        
        context->getDirectCommandQueue().executeCommandList(list);
        context->getDirectCommandQueue().flush();
        context->swapBuffers();
    }

    return 0;
}