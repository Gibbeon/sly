#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/devicebuilder.h"

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
        
        class IDevice {
        public:        
            virtual ~IDevice() {} 
            virtual void init(DeviceDesc& desc) =0;

            virtual void createWindow(IWindow** ppWindow, WindowDesc& desc) = 0;
            virtual void createCommandQueue(ICommandQueue** queue, CommandQueueDesc& desc) = 0;
            virtual void createCommandList(ICommandList** ppWindow, CommandListDesc& desc) = 0;
            virtual void createRenderState(IRenderState** ppWindow, RenderStateDesc& desc) = 0;
            virtual void createShader(IShader** ppWindow, ShaderDesc& desc) = 0;
            virtual void createTexture(ITexture** ppWindow, TextureDesc& desc) = 0;
            virtual void createVertexBuffer(IVertexBuffer** ppWindow, VertexBufferDesc& desc) = 0;
            virtual void createIndexBuffer(IIndexBufer** ppWindow, IndexBufferDesc& desc) = 0;

            // render target, stencil buffer, etc? need to review this some more
            
        protected:
            IDevice() {} 
        };
    }
}