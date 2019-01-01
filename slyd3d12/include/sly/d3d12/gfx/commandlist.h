#pragma once

#include "sly/d3d12.h"
#include "sly/gfx/commandlist.h"
#include "sly/math.h"
#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/rendertarget.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;

        class D3D12CommandListImpl: public ICommandList {
        public:
            D3D12CommandListImpl(ref_t<D3D12DeviceImpl> device, ref_t<CommandListDesc> desc = DEFAULT_DESC);

            virtual void begin();
            virtual void end();

            virtual void setRenderState(ref_t<IRenderState> state);
            virtual void setViewport(ref_t<Viewport> viewport);
            virtual void setScissorRect(rect_t<long> rect);
            virtual void setVertexBuffer(ref_t<IVertexBuffer> buffer);
            virtual void setRenderTarget(ref_t<IRenderTarget> target);
            
            virtual void clear(color_t<> color);
            virtual void draw(size_t, size_t, size_t, size_t);

            //virtual void setViewport();
            //virtual void setCamera();
            //virtual void setProjection();
            //virtual void setScissorRect();
            //virtual void setVSShader();
            //virtual void setPSShader();
            //virtual void setVertexBuffer();
            //virtual void setIndexBuffer();
            //virtual void setTexture();

            //virtual void drawIndexed();

            //virtual bool_t Draw(ptr_t<IGfxVertexBuffer> buffer, ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE descriptor);
            //virtual bool_t Draw(ptr_t<IGfxVertexBuffer> buffer, ptr_t<IGfxWindow> window);

            ref_t<ID3D12CommandList>    getID3D12CommandList() { return list_; }
            ref_t<ID3D12CommandAllocator>       getID3D12CommandAllocator() { return allocator_; }
            
        protected:
            //using D3D12RenderStateImpl::D3D12RenderStateImpl;

        private:
            ref_t<ID3D12GraphicsCommandList> list_;
            ref_t<ID3D12CommandAllocator> allocator_;
            ref_t<D3D12RenderTargetImpl> target_;
            ref_t<D3D12RenderStateImpl> renderState_;
        };
    }
}