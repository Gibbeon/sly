#pragma once

#include "sly/global.h"
#include "sly/gfx/builders/devicebuilder.h"
#include "sly/gfx/builders/rendercontextbuilder.h"
#include "sly/gfx/builders/commandlistbuilder.h"
#include "sly/gfx/builders/shaderbuilder.h"
#include "sly/gfx/builders/vertexbufferbuilder.h"
#include "sly/gfx/builders/renderstatebuilder.h"
#include "sly/os/window.h"

namespace sly {
    namespace gfx {  
        class IRenderContext;
        class ICommandList;
        class IResource;
        class IShader;
        class ITexture;
        class ICommandQueue;
        class IIndexBufer;
        class IVertexBuffer;
        class IRenderState;

        struct RenderContextDesc;
        struct CommandListDesc;
        struct ResourceDesc;
        struct ShaderDesc;
        struct TextureDesc;
        struct CommandQueueDesc;
        struct BufferDesc;
        struct RenderStateDesc;
        
        class IDevice {
        public:        
            virtual ~IDevice() {} 
            virtual retval<void> init(const DeviceDesc& desc = DeviceBuilder().build()) = 0;
            virtual retval<void> release() = 0;

            virtual retval<std::unique_ptr<IRenderContext>> createRenderContext(os::IWindow& window, const RenderContextDesc& desc = RenderContextBuilder().build()) = 0;
            virtual retval<ICommandList*> createCommandList(const CommandListDesc& desc = CommandListBuilder().build()) = 0;
            virtual retval<IShader*> createShader(const ShaderDesc& desc = ShaderBuilder().build()) =0;
            virtual retval<IVertexBuffer*> createVertexBuffer(const BufferDesc& desc = BufferBuilder().build()) = 0;
            virtual retval<IRenderState*> createRenderState(const RenderStateDesc& desc = RenderStateBuilder().build()) = 0;

            //virtual void createRenderContext(IRenderContext** ppWindow, const RenderContextDesc& desc) = 0;
            virtual void createCommandQueue(ICommandQueue** queue,  const CommandQueueDesc& desc) = 0;
            //virtual void createCommandList(ICommandList** ppWindow,  const CommandListDesc& desc) = 0;
            //virtual void createRenderState(IRenderState** ppWindow,  const RenderStateDesc& desc) = 0;
            virtual void createTexture(ITexture** ppWindow,  const TextureDesc& desc) = 0;
            virtual void createIndexBuffer(IIndexBufer** ppWindow,  const BufferDesc& desc) = 0;

            // render target, stencil buffer, etc? need to review this some more
            
        protected:
            IDevice() {} 
        };
    }
}