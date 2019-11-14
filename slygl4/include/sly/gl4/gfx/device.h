#pragma once

#include "sly/gl4.h"
#include "sly/gfx.h"
#include "sly/gl4/renderingdevice.h"

namespace sly {
	namespace gfx {
		class GL4Device : public IDevice {
			virtual void init(Device& desc) {}

            virtual void createWindow(IRenderContext** ppWindow, Window& desc) {
				(*ppWindow) = new GL4Window();
			}

            virtual void createCommandQueue(ICommandQueue** queue, CommandQueue& desc) {}
            virtual void createCommandList(ICommandList** ppWindow, CommandList& desc) {}
            virtual void createRenderState(IRenderState** ppWindow, RenderState& desc) {}
            virtual void createShader(IShader** ppWindow, Shader& desc) {}
            virtual void createTexture(ITexture** ppWindow, Texture& desc) {}
            virtual void createVertexBuffer(IVertexBuffer** ppWindow, VertexBuffer& desc) {}
            virtual void createIndexBuffer(IIndexBufer** ppWindow, IndexBuffer& desc) {}
		};
    }
} 