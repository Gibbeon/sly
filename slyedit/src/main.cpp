
#include "sly.h"
#include "sly/engine.h"
#include "sly/scene.h"
#include "sly/d3d12.h"
//#include "sly/d3d12/gfx/commandlist.h"
#include "sly/io/memorystream.h"
#include "sly/runtime/serialization/json/jsonserializer.h"
#include "sly/runtime/serialization/json/jsondeserializer.h"

#if !_WIN32
    // MacOS shader
    const char shadersSrc[] = R"""(
        #include <metal_stdlib>
        using namespace metal;
        vertex float4 VSMain(
            const device packed_float3* vertexArray [[buffer(0)]],
            unsigned int vID[[vertex_id]])
        {
            return float4(vertexArray[vID], 1.0);
        }
        fragment half4 PSMain()
        {
            return half4(1.0, 0.0, 0.0, 1.0);
        }
    )""";
    #else
    const char shadersSrc[] = R"""(
        struct PSInput
        {
            float4 position : SV_POSITION;
            float4 color : COLOR;
        };

        PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
        {
            PSInput result;

            result.position = position;
            result.color = color;

            return result;
        }

        float4 PSMain(PSInput input) : SV_TARGET
        {
            return input.color;
        }
    )""";
    #endif

struct Vec3 {
    float x, y, z;
};

struct Vertex
{
    Vec3 position;
    sly::gfx::color_t color;
};

void configureRenderInterfaces(const sly::Engine& engine) {
    #ifdef _WIN32
        engine.kernel().graphics().interfaces().push_back(sly::d3d12::gfx::GetRenderInterface());
    #else
        engine.kernel().gfx().interfaces().push_back(sly::gfx::METAL::GetRenderInterface());
    #endif  
}


class TestScene : public sly::Scene {
public:
    virtual sly::retval<void> update() {
        LOG_VERBOSE("TestScene");
        return sly::success();
    }
};

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
#else
int main()
#endif
{   
    sly::Engine* engine = &sly::Engine();

    S_LOG_VERBOSE("Hi");

    // load configuration, plugins, etc
    Ensures(engine->init().succeeded());

    configureRenderInterfaces(*engine);

    //get the first interface
    auto gfxapi                  = engine->kernel().graphics().interfaces().at(0);
    
    auto window                  = engine->kernel().windows().create(
        sly::os::WindowBuilder()
            .setHeight(768)
            .setWidth(1024)
            .setTitle("Hi!")
            .build()       
    ); // window desc
    
    auto device                  = gfxapi->createDevice(); //device desc
    auto context                 = device->createRenderContext(*window.result());

    window->setVisible(true);


    //engine->activator().add<TestScene>();
    engine->activator().add<sly::SimpleMesh>();

    engine->resources().mount("slyedit/data");

    std::shared_ptr<sly::Scene> scene;
    auto value = engine->resources().find("scene")->create<sly::Scene>();

    scene = value.result();

    while(true) {
        //engine->begin();
        engine->update();

        scene->update();
        scene->draw(context);

        window->processMessages();
        context->present();

        //engine->draw();
        //engine->present();
        //engine->end();
    }

    //scene->release();

    /*auto list = device->createCommandList();

    auto vsshader = device->createShader(
        sly::gfx::ShaderBuilder()
            .setData((vptr_t)shadersSrc, sizeof(shadersSrc))
            .setEntryPoint("VSMain")
            .setTarget("vs_5_0")
            .build()
    );

    auto psshader = device->createShader(
        sly::gfx::ShaderBuilder()
            .setData((vptr_t)shadersSrc, sizeof(shadersSrc))
            .setEntryPoint("PSMain")
            .setTarget("ps_5_0")
            .build()
    );

    auto pVertexData = engine->kernel().filesystem().open("vertex.dat");
    size_t vtxsize = pVertexData->stream()->size();

    std::unique_ptr<Vertex[]> triangleVertices = std::make_unique<Vertex[]>(vtxsize/sizeof(Vertex));
    pVertexData->stream()->read(triangleVertices.get(), vtxsize);
    pVertexData->close();
    
    auto vertexBuffer = device->createVertexBuffer(
        sly::gfx::VertexBufferBuilder()
            .setData(triangleVertices.get(), vtxsize / sizeof(Vertex), sizeof(Vertex))
            .build()
    ); 

    auto rsState = device->createRenderState( 
        sly::gfx::RenderStateBuilder()
            .setVSShader(vsshader) //renderPipelineDesc.SetVertexFunction(vertFunc);
            .setPSShader(psshader) //renderPipelineDesc.SetFragmentFunction(fragFunc);
            .setPrimitiveType(sly::gfx::ePrimativeType_Triangle)
            .setRTVFormats(0, sly::gfx::eDataFormat_R8G8B8A8_UNORM) //renderPipelineDesc.GetColorAttachments()[0].SetPixelFormat(mtlpp::PixelFormat::BGRA8Unorm);
            .addInputElementDesriptor(            
                sly::gfx::InputElementBuilder()
                    .setSemanticName("POSITION")
                    .setFormat(sly::gfx::eDataFormat_R32G32B32_FLOAT)
                    .build()
            )
            .addInputElementDesriptor(
                sly::gfx::InputElementBuilder()
                    .setSemanticName("COLOR")
                    .setFormat(sly::gfx::eDataFormat_R32G32B32A32_FLOAT)
                    .setOffset(12)
                    .build()
            )
            .build()
    );

    sly::gfx::Viewport viewport(0, 0, 1024, 768);
    sly::rect_t<> scissorRect(0, 0, 1024, 768);
    sly::gfx::color_t clearColor(.4f, .4f, .4f, 0.5f);

    std::vector<sly::gfx::ICommandList*> lists;
    lists.push_back(list);

    while(true) {
        //scene->update();
        //list->begin();
        //list->setRenderState(rsState);
        //list->setRenderTarget(context->getDrawBuffer());
        //list->clear(clearColor);
        //list->setViewport(viewport);    
        //list->setScissorRect(scissorRect);
        //list->setVertexBuffer(vertexBuffer);
        //list->draw(3, 1, 0, 0);
        //list->end(); 

        context->update();     

        context->commandQueue().executeCommandLists(lists);
        context->commandQueue().flush();

        context->present();
    }
    */

    //rsState->release();
    //psshader->release();
    //vsshader->release();
    //list->release();
    context->release();
    device->release();
    window->release();
    engine->release();

    return 0;

#ifdef NO

    engine->filesystem().mount("/data");

    sly::Scene* scene = &sly::Scene(engine, context);
    scene->load("scene");
    
    sly::Stopwatch stopwatch(true);
    while(true) {
        
        delta = stopwatch.reset();
        
        scene->update(delta);
        
        context->draw();
        context->present();
    }
    stopwatch.stop();

    scene->release();
    engine->filesystem().unmount("/data");
    
    device->release();
    window->release();
    gfxapi->release();
    engine->release();










    // create a device context, this managers resources for the render system
    auto renderDevice = engine.graphics().createDevice(sly::gfx::DeviceBuilder().build());

    if(renderDevice.failed()) {
        
        return renderDevice.statusCode();
    }

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

    Vertex* triangleVertices = nullptr;
    auto pVertexData = engine.filesystem().open("vertex.dat");

    if(pVertexData.failed()) {
        throw;
    }

    size_t vtxsize = pVertexData->stream()->getSize();
    
    triangleVertices = (Vertex*)malloc(vtxsize);
    pVertexData->stream()->read(triangleVertices, vtxsize);
    //pVertexData->close();

    vbBuilder.setData(triangleVertices, vtxsize / sizeof(Vertex), sizeof(Vertex));

    

    vsspBuilder.setData((vptr_t)shadersSrc, sizeof(shadersSrc))
                .setEntryPoint("VSMain")
                .setName("shaders")
                .setTarget("vs_5_0");

    psspBuilder.setData((vptr_t)shadersSrc, sizeof(shadersSrc))
                .setEntryPoint("PSMain")
                .setName("shaders")
                .setTarget("ps_5_0");

    sly::gfx::IVertexBuffer* vertexBuffer = nullptr;
    renderDevice->createVertexBuffer(&vertexBuffer, vbBuilder.build()); 

    sly::gfx::IShader* psshader = nullptr;
    sly::gfx::IShader* vsshader = nullptr;

    renderDevice->createShader(&vsshader, vsspBuilder.build()); 
    renderDevice->createShader(&psshader, psspBuilder.build()); 

    // render state
    sly::gfx::RenderStateBuilder rstBuilder;
    rstBuilder
        .setVSShader(*vsshader) //renderPipelineDesc.SetVertexFunction(vertFunc);
        .setPSShader(*psshader) //renderPipelineDesc.SetFragmentFunction(fragFunc);
        .setSampleMax(UINT_MAX)
        .setPrimitiveType(sly::gfx::ePrimativeType_Triangle)
        .setNumberRenderTargets(1)
        .setRTVFormats(0, sly::gfx::eDataFormat_R8G8B8A8_UNORM) //renderPipelineDesc.GetColorAttachments()[0].SetPixelFormat(mtlpp::PixelFormat::BGRA8Unorm);
        .setSampleDesc(1)
        .addInputElementDesriptor(posBuilder1.build())
        .addInputElementDesriptor(posBuilder2.build());

    // render state
    //mtlpp::RenderPipelineDescriptor renderPipelineDesc;
    sly::gfx::IRenderState* rsState = nullptr;
    renderDevice->createRenderState(&rsState, rstBuilder.build()); //g_renderPipelineState = g_device.NewRenderPipelineState(renderPipelineDesc, nullptr);

    //mtlpp::CommandBuffer commandBuffer = g_commandQueue.CommandBuffer(); // to get list
    // loop
    //list->begin(); //    mtlpp::RenderCommandEncoder renderCommandEncoder = commandBuffer.RenderCommandEncoder(renderPassDesc);
    //list->setRenderState(*rsState); //    renderCommandEncoder.SetRenderPipelineState(g_renderPipelineState);
    //list->setRenderTarget(context->getDrawBuffer());
    //list->setViewport(viewport);    
    //list->setScissorRect(scissorRect);
    //list->clear(clearColor);
    //list->setVertexBuffer(*vertexBuffer); //    renderCommandEncoder.SetVertexBuffer(g_vertexBuffer, 0, 0);
    //list->draw(3, 1, 0, 0); //    renderCommandEncoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
    //list->end();  //    renderCommandEncoder.EndEncoding();

    //context->processMessages();        
    //context->getDirectCommandQueue().executeCommandList(list); //    commandBuffer.Present(m_view.GetDrawable());
    //context->getDirectCommandQueue().flush(); //commandBuffer.Commit();
    //context->swapBuffers(); 
    //commandBuffer.WaitUntilCompleted();

    // state
    sly::gfx::Viewport viewport(0, 0, 1024, 768);
    sly::rect_t scissorRect(0, 0, 1024, 768);
    sly::gfx::color_t clearColor(.4f, .4f, .4f, 1.0f);

    while(true) {
        #if _WIN32
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
        #else                                                               //01 - mtlpp::CommandBuffer commandBuffer = g_commandQueue.CommandBuffer();
        // loop                                                             //02 - mtlpp::RenderPassDescriptor renderPassDesc = m_view.GetRenderPassDescriptor();
        //list->begin();                                                    //03 -     mtlpp::RenderCommandEncoder renderCommandEncoder = commandBuffer.RenderCommandEncoder(renderPassDesc);
        //list->setRenderState(*rsState);                                   //04 -     renderCommandEncoder.SetRenderPipelineState(g_renderPipelineState);
        //list->setRenderTarget(context->getDrawBuffer());                  //08 - commandBuffer.Present(m_view.GetDrawable());
        //list->setVertexBuffer(*vertexBuffer);                             //05 -     renderCommandEncoder.SetVertexBuffer(g_vertexBuffer, 0, 0);
        //list->draw(3, 1, 0, 0);                                           //06 -     renderCommandEncoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
        //list->end();                                                      //07 -     renderCommandEncoder.EndEncoding();
        
        //09 - commandBuffer.Commit();

        context->processMessages();        
        //context->getDirectCommandQueue().executeCommandList(list);        
        //context->getDirectCommandQueue().flush();                         //09 - commandBuffer.Commit();
        context->swapBuffers();                                             //10 - commandBuffer.WaitUntilCompleted();
        #endif
    }
    
    return  0;




    #define TEST_ASSETREADER 1
    #if !TEST_ASSETREADER
    
        
   
    #else

        sly::IInputStream* pShaderJson;
        sly::Engine::OS().FileSystem().open(&pShaderJson, "shaders.json");        
        sly::TextReader reader(*pShaderJson);

        auto j3 = json::parse((const char_t*)reader.readAll());

        sly::IInputStream* pShaderFile;
        sly::Engine::OS().FileSystem().open(&pShaderFile, j3[0]["file"].get<std::string>().c_str());        

        size_t vssize = pShaderFile->getSize();
        char* vsbuf = (char*)malloc(vssize);
        pShaderFile->read(vsbuf, vssize);

        vsspBuilder.setData(vsbuf, vssize)
                    .setEntryPoint(j3[0]["entryPoint"].get<std::string>().c_str())
                    .setName(j3[0]["name"].get<std::string>().c_str())
                    .setTarget(j3[0]["target"].get<std::string>().c_str());

        psspBuilder.setData(vsbuf, vssize)
                    .setEntryPoint(j3[1]["entryPoint"].get<std::string>().c_str())
                    .setName(j3[1]["name"].get<std::string>().c_str())
                    .setTarget(j3[1]["target"].get<std::string>().c_str());
                    
        
        /*sly::TypeActivator activator;

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
        vsspBuilder.init(vsspDesc);*/
    #endif
   

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
#endif
}