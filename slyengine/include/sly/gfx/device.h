#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {  
        class IWindow;
        class ICommandList;
        class IResource;
        class IShader;
        class ITexture;
        class ICommandQueue;
        class IIndexBufer;
        class IVertexBuffer;
        class IRenderState;

        struct WindowDesc;
        struct CommandListDesc;
        struct ResourceDesc;
        struct ShaderDesc;
        struct TextureDesc;
        struct CommandQueueDesc;
        struct VertexBufferDesc;
        struct IndexBufferDesc;
        struct RenderStateDesc;

        struct DeviceDesc {
        public:
        };
        
        class IDevice {
        public:
            virtual void createWindow(out_ptr_t<IWindow> ppWindow, ref_t<WindowDesc> desc) = 0;
            virtual void createCommandQueue(out_ptr_t<ICommandQueue> queue, ref_t<CommandQueueDesc> desc) = 0;
            virtual void createCommandList(out_ptr_t<ICommandList> ppWindow, ref_t<CommandListDesc> desc) = 0;
            virtual void createRenderState(out_ptr_t<IRenderState> ppWindow, ref_t<RenderStateDesc> desc) = 0;
            virtual void createShader(out_ptr_t<IShader> ppWindow, ref_t<ShaderDesc> desc) = 0;
            virtual void createTexture(out_ptr_t<ITexture> ppWindow, ref_t<TextureDesc> desc) = 0;
            virtual void createVertexBuffer(out_ptr_t<IVertexBuffer> ppWindow, ref_t<VertexBufferDesc> desc) = 0;
            virtual void createIndexBuffer(out_ptr_t<IIndexBufer> ppWindow, ref_t<IndexBufferDesc> desc) = 0;
            
            constexpr static DeviceDesc DEFAULT_DESC = {  }; 
        protected:
            friend class DeviceBuilder;
        };

        class DeviceBuilder : public Builder<DeviceDesc> {
        public:
            DeviceBuilder() : Builder(IDevice::DEFAULT_DESC) {}
        };

    }
}