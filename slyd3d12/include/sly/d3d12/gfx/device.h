#pragma once

#include "sly/d3d12.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl : public IDevice {
        public:
            D3D12DeviceImpl(ref_t<DeviceDesc> desc = IDevice::DEFAULT_DESC);
            
            virtual void createWindow(out_ptr_t<IWindow> ppWindow, ref_t<WindowDesc> desc);
            virtual void createCommandQueue(out_ptr_t<ICommandQueue> queue, ref_t<CommandQueueDesc> desc);
            virtual void createCommandList(out_ptr_t<ICommandList> ppWindow, ref_t<CommandListDesc> desc);
            virtual void createRenderState(out_ptr_t<IRenderState> ppWindow, ref_t<RenderStateDesc> desc);
            virtual void createShader(out_ptr_t<IShader> ppWindow, ref_t<ShaderDesc> desc);
            virtual void createTexture(out_ptr_t<ITexture> ppWindow, ref_t<TextureDesc> desc);
            virtual void createVertexBuffer(out_ptr_t<IVertexBuffer> ppWindow, ref_t<VertexBufferDesc> desc);
            virtual void createIndexBuffer(out_ptr_t<IIndexBufer> ppWindow, ref_t<IndexBufferDesc> desc);
 
            ref_t<IDXGIAdapter1> getIDXGIAdapter1()   { return adapter_; }
            ref_t<IDXGIFactory4> getIDXGIFactory4()   { return factory_; }
            ref_t<ID3D12Device> getID3D12Device()   { return device_; }

        private:
            ref_t<IDXGIFactory4>  factory_;
            ref_t<IDXGIAdapter1>  adapter_;
            ref_t<ID3D12Device>   device_;
        };
    }
}