

#ifdef _WIN32
#include <windows.h>
//#include <io.h>
//#include <fcntl.h>
//#include <iostream>
//#include <cstdio>

// how to do a debug console with windows
    /*
    if (AllocConsole()) {
        int fout = 0;
        _sopen_s(&fout, "CONOUT$", _O_WRONLY, _SH_DENYNO, _S_IWRITE);
        char *hello = "Hello world!\n";
        _write(fout, hello, strlen (hello));

        LPSTR goodbye = "Goodbye, cruel world!\n";
        DWORD length = strlen(goodbye);
        DWORD written;
        WriteConsole((HANDLE)_get_osfhandle(fout), goodbye, length, &written, NULL);

        _close(fout);
        //ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &c, 1, &n, 0);
    }*/

#endif

#include <gsl/gsl>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

#include "sly.h"

#include "sly/os/os.h"
#include "sly/gfx.h"

#include "sly/runtime/serialization/serializer.h"
#include "sly/io/binarywriter.h"

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

// things to do
// window create through os instead of render context
// mount directory/file & resource lookup system
// resources
//  vertex buffer
//  texture
//  camera
// need a better plugin system
// must debug log
// need to standardize on an error paradigm
// need to check errors everywhere throughout system

namespace sly {

/*
    typedef enum {
        eMountType_Unused = 0,
        eMountType_Directory
    } eMountType;

    class ResourceManager {
    public:
        const static size_t MAX_MOUNT = 16;

        ResourceManager() {
            memset(_records, 0, sizeof(Record));
        }

        s32     mount(eMountType type, String moniker) {
            s32 index = getFirstFree();
            if(index >= 0) {
                _records[index].type = type;
                _records[index].handle = (vptr_t)moniker.c_str();
            }

            return index;
        }

        void    unmount(u32 slot) {
            _records[slot].type = eMountType_Unused;
        }

        void    getStream(s32 slot, sly::IInputStream** stream, String moniker) {
            switch(_records[slot].type) {
                case eMountType_Directory:
                    sly::Engine::OS().FileSystem().open(stream, moniker.c_str());
                    break;
            }            
        }

        sly::ResourceReader getResource(s32 slot, String moniker) {
            switch(_records[slot].type) {
                case eMountType_Directory:
                    IInputStream* stream;
                    getStream(slot, &stream, moniker + ".json");
                    return sly::ResourceReader(new JSONDeserializer(stream));
                    break;
            }            
        }

    private:

        s32 getFirstFree() {
            for(size_t i = 0; i < MAX_MOUNT; i++) {
                if(_records[i].type == eMountType_Unused)
                    return i;
            }
            return -1;
        }

        typedef struct {
            eMountType type;
            vptr_t handle;
        } Record;

        Record _records[MAX_MOUNT];
    };

    class ResourceReader { // IReader
    public:
        ResourceReader(IDeserializer* deserializer): 
            _deserializer(deserializer)
        {

        };

        template<typename T>
        T read() {
            return _deserializer->read<T>();            
        }

    private:
        IDeserializer* _deserializer;
    };

    /*
        {
            name: "name",
            renderstate: {   
                clearColor:
                {
                    r: .4,
                    g: .4,
                    b: .4,
                    a: 1
                },          
                viewport: 
                {
                    name: "name",
                    left: 0,
                    top: 0,
                    width: 1024,
                    height: 768
                },
                scissorRect:                     
                {
                    name: "name",
                    left: 0,
                    top: 0,
                    width: 1024,
                    height: 768
                }
            },
            entities: [
                {
                    name: "name",
                    type: "SimpleMesh",
                    data:
                    {
                        verticies: {
                            ref: "vertex.dat"
                        },
                        shaders: [
                            {
                                type: "vertex",
                                name: "VSMain",
                                ref: "shaders.hlsl"
                            },
                            {
                                type: "pixel",
                                name: "PSMain",
                                ref: "shaders.hlsl"
                            },
                        ]
                    }
                }
            ]
        }
    */

    //sly::gfx::Viewport viewport(0, 0, 1024, 768);
    //sly::rect_t scissorRect(0, 0, 1024, 768);
    //sly::gfx::color_t clearColor(.4f, .4f, .4f, 1.0f);

    class Scene {

    };
}

    

int doRenderStuff();

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
#else
int main()
#endif
{  
    sly::EngineBuilder engBuilder;

    //sly::StackAlloc<4096> buffer;

    //engBuilder
    //    .setSystemMemoryHeap(sly::eSystemMemoryHeap_Default,    sly::MemoryHeapBuilder().setBytes(buffer, buffer.size).setDebug(true).build())
    //    .setSystemMemoryHeap(sly::eSystemMemoryHeap_Resources,  sly::MemoryHeapBuilder().setSize(1024 * 1024 * 32).setDebug(true).build())
    //    .setSystemMemoryHeap(sly::eSystemMemoryHeap_Debug,      sly::MemoryHeapBuilder().setSize(1024 * 1024 * 32).setDebug(true).build())
    //    .setLogLevel(sly::eLogLevel_Info);

    // load configuration, plugins, etc
    sly::Engine::init(engBuilder.build());

    //int slot = sly::Engine::Resources()->mount(sly::eMountType_Directory, "./data");
    
    //sly::ResourceReader reader;
    //sly::Engine::Resources()->getResource(slot, &reader, "object");

    //sly::Scene scene = rdr->read<sly::Scene>();

    //scene->render(renderContext);

    //sly::Engine::Resources()->unmount(slot);

    doRenderStuff();
}

int doRenderStuff() {

    // choosing between multiple render systems? -- this points to an API d3d12, opengl, etc.
    auto renderSystem = sly::Engine::createRenderSystem(sly::gfx::RenderSystemBuilder().build());

    if(renderSystem.failed()) {
        // handle exception
    }

    // create a device context, this managers resources for the render system
    sly::gfx::IDevice* renderDevice = nullptr; // device becomes renderer???
    renderSystem->createDevice(&renderDevice, sly::gfx::DeviceBuilder().build());

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
    sly::IInputStream* pVertexData;
    sly::Engine::OS().FileSystem().open(&pVertexData, "vertex.dat");

    size_t vtxsize = pVertexData->getSize();
    
    triangleVertices = (Vertex*)malloc(vtxsize);
    pVertexData->read(triangleVertices, vtxsize);
    //pVertexData->close();

    vbBuilder.setData(triangleVertices, vtxsize / sizeof(Vertex), sizeof(Vertex));

    // MacOS shader
    /*const char shadersSrc[] = R"""(
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
    )""";*/

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
    
    return  0;

#ifdef TURN_OFF



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