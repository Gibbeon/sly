#pragma once

#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl : public IDevice {
        public:
            D3D12DeviceImpl(IRenderer& system);
            virtual void init(DeviceDesc& desc);
            
            virtual void createRenderContext(IRenderContext** ppWindow, RenderContextDesc& desc);
            virtual void createCommandQueue(ICommandQueue** queue, CommandQueueDesc& desc);
            virtual void createCommandList(ICommandList** ppWindow, CommandListDesc& desc);
            virtual void createRenderState(IRenderState** ppWindow, RenderStateDesc& desc);
            virtual void createShader(IShader** ppWindow, ShaderDesc& desc);
            virtual void createTexture(ITexture** ppWindow, TextureDesc& desc);
            virtual void createVertexBuffer(IVertexBuffer** ppWindow, VertexBufferDesc& desc);
            virtual void createIndexBuffer(IIndexBufer** ppWindow, IndexBufferDesc& desc);
 
            IDXGIAdapter1& getIDXGIAdapter1()   { return *_adapter; }
            IDXGIFactory4& getIDXGIFactory4()   { return *_factory; }
            ID3D12Device& getID3D12Device()   { return *_device; }

        private:
            IRenderer* _system;
            IDXGIFactory4*  _factory;
            IDXGIAdapter1*  _adapter;
            ID3D12Device*   _device;
        };
    }
}