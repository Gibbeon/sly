#pragma once

#include "sly/gl4.h"
#include "sly/gfx.h"
#include "sly/gl4/renderingdevice.h"

namespace sly {
	namespace gfx {
		class GL4Device : public IDevice {
			virtual void init(DeviceDesc& desc) {}

            virtual void createWindow(IWindow** ppWindow, WindowDesc& desc) {
				(*ppWindow) = new GL4Window();
			}

            virtual void createCommandQueue(ICommandQueue** queue, CommandQueueDesc& desc) {}
            virtual void createCommandList(ICommandList** ppWindow, CommandListDesc& desc) {}
            virtual void createRenderState(IRenderState** ppWindow, RenderStateDesc& desc) {}
            virtual void createShader(IShader** ppWindow, ShaderDesc& desc) {}
            virtual void createTexture(ITexture** ppWindow, TextureDesc& desc) {}
            virtual void createVertexBuffer(IVertexBuffer** ppWindow, VertexBufferDesc& desc) {}
            virtual void createIndexBuffer(IIndexBufer** ppWindow, IndexBufferDesc& desc) {}
		};
    }
} 