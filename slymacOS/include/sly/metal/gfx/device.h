#pragma once

#include "sly/metal.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        class METALDeviceImpl : public IDevice {
        public:
            METALDeviceImpl(IRenderInterface& system);
            virtual void init(DeviceDesc& desc);
            
            virtual void createRenderContext(IRenderContext** ppWindow, RenderContextDesc& desc);
            virtual void createCommandQueue(ICommandQueue** queue, CommandQueueDesc& desc);
            virtual void createCommandList(ICommandList** ppWindow, CommandListDesc& desc);
            virtual void createRenderState(IRenderState** ppWindow, RenderStateDesc& desc);
            virtual void createShader(IShader** ppWindow, ShaderDesc& desc);
            virtual void createTexture(ITexture** ppWindow, TextureDesc& desc);
            virtual void createVertexBuffer(IVertexBuffer** ppWindow, BufferDesc& desc);
            virtual void createIndexBuffer(IIndexBufer** ppWindow, BufferDesc& desc);
 
            //IDXGIAdapter1& getIDXGIAdapter1()   { return *_adapter; }
            //IDXGIFactory4& getIDXGIFactory4()   { return *_factory; }
            mtlpp::Device& getMETALDevice()   { return _device; }

        private:
            IRenderInterface& _system;
            mtlpp::Device  _device;
            //IDXGIFactory4*  _factory;
            //IDXGIAdapter1*  _adapter;
        };
    }
}