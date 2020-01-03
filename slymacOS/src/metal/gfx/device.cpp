#include "sly/metal/gfx/device.h"
#include "sly/metal/gfx/commandqueue.h"
#include "sly/metal/gfx/commandlist.h"
#include "sly/metal/gfx/rendercontext.h"
#include "sly/metal/gfx/vertexbuffer.h"
#include "sly/metal/gfx/indexbuffer.h"
#include "sly/metal/gfx/shader.h"
#include "sly/metal/gfx/renderstate.h"
#include "sly/metal/gfx/texture.h"
#include "sly/macos/os/window.h"
#include "mtlpp/mtlpp.hpp"

using namespace sly::gfx;

METALDeviceImpl::METALDeviceImpl(IRenderer& system) : _system(system)
{
    
}

void METALDeviceImpl::init(DeviceDesc& desc) 
{
    _device = mtlpp::Device::CreateSystemDefaultDevice();
    
    /*UINT dxgiFactoryFlags = 0;

    #ifdef _DEBUG
    {
        IMETALDebug* debugController;
        if (SUCCEEDED(METALGetDebugInterface(IID_IMETALDebug, reinterpret_cast<vptr_t*>(&debugController))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
    #endif

    CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory4, reinterpret_cast<vptr_t*>(&_factory));

    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != _factory->EnumAdapters1(adapterIndex, &_adapter); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        _adapter->GetDesc1(&desc);

        if (SUCCEEDED(METALCreateDevice(_adapter, D3D_FEATURE_LEVEL_11_0, IID_IMETALDevice, reinterpret_cast<vptr_t*>(&_device))))
        {
            break;
        }
    }*/
}

void METALDeviceImpl::createRenderContext(IRenderContext** ppWindow, RenderContextDesc& desc) {
    
    sly::os::WindowBuilder builder;
    builder.setHeight(768).setWidth(1024).setTitle("Hi!");

    auto window = new sly::os::MacOSWindow();
    window->init(builder.build());

    window->show();
    
    (*ppWindow) = new METALRenderContextImpl(*this, *window);
    (*ppWindow)->init(desc);
}

void METALDeviceImpl::createCommandQueue(ICommandQueue** queue, CommandQueueDesc& desc) {
    (*queue) = new METALCommandQueueImpl(*this);
    (*queue)->init(desc);
}

void METALDeviceImpl::createCommandList(ICommandList** ppWindow, CommandListDesc& desc) {
    (*ppWindow) = new METALCommandListImpl(*this);
    (*ppWindow)->init(desc);
}

void METALDeviceImpl::createRenderState(IRenderState** ppWindow, RenderStateDesc& desc) {
    (*ppWindow) = new METALRenderStateImpl(*this);
    (*ppWindow)->init(desc);
}

void METALDeviceImpl::createShader(IShader** ppWindow, ShaderDesc& desc) {
    (*ppWindow) = new METALShaderImpl(*this);
    (*ppWindow)->init(desc);
}

void METALDeviceImpl::createTexture(ITexture** ppWindow, TextureDesc& desc) {}

void METALDeviceImpl::createVertexBuffer(IVertexBuffer** ppWindow, VertexBufferDesc& desc) {
    (*ppWindow) = new METALVertexBufferImpl(*this);
    (*ppWindow)->init(desc);
}

void METALDeviceImpl::createIndexBuffer(IIndexBufer** ppWindow, IndexBufferDesc& desc) {}

