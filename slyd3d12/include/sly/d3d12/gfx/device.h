#pragma once

#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {
        class D3D12DeviceImpl : public IDevice {
        public:
            D3D12DeviceImpl(IRenderInterface& system);
            virtual retval<void> init(const DeviceDesc& desc = DeviceBuilder().build());
            virtual retval<void> release();
            
            virtual retval<std::unique_ptr<IRenderContext>> createRenderContext(os::IWindow& window, const RenderContextDesc& desc = RenderContextBuilder().build());
            virtual retval<ICommandList*> createCommandList(const CommandListDesc& desc = CommandListBuilder().build());
            virtual retval<IShader*> createShader(const ShaderDesc& desc = ShaderBuilder().build());
            virtual retval<IVertexBuffer*> createVertexBuffer(const BufferDesc& desc = BufferBuilder().build());
            virtual retval<IRenderState*> createRenderState(const RenderStateDesc& desc = RenderStateBuilder().build());

            //virtual void createRenderContext(IRenderContext** ppWindow, const RenderContextDesc& desc);
            virtual void createCommandQueue(ICommandQueue** queue, const CommandQueueDesc& desc);
            //virtual void createRenderState(IRenderState** ppWindow, const RenderStateDesc& desc);
            virtual void createTexture(ITexture** ppWindow, const TextureDesc& desc);
            virtual void createIndexBuffer(IIndexBufer** ppWindow, const BufferDesc& desc);
 
            IDXGIAdapter1& getIDXGIAdapter1()   { return *_adapter; }
            IDXGIFactory4& getIDXGIFactory4()   { return *_factory; }
            ID3D12Device& getID3D12Device()   { return *_device; }

        private:
            IRenderInterface*   _system;
            gsl::owner<IDXGIFactory4*>      _factory;
            gsl::owner<IDXGIAdapter1*>      _adapter;
            gsl::owner<ID3D12Device*>       _device;
            gsl::owner<ID3D12Debug*>        _debugTask;
            bool_t              _initialized;
        };
    }
}