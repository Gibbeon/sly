

#include <windows.h>
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



#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
#else
int main()
#endif
{  
     // load configuration, plugins, etc
    sly::Engine::init();    

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

    return 0;
}