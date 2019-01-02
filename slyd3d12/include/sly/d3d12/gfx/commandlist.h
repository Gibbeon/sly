#pragma once

#include "sly/d3d12.h"
#include "sly/gfx/commandlist.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/renderstate.h"
#include "sly/d3d12/gfx/rendertarget.h"

namespace sly {
    namespace gfx {

        class D3D12DeviceImpl;

        class D3D12CommandListImpl: public ICommandList {
        public:
            D3D12CommandListImpl(D3D12DeviceImpl& device);
            virtual void init(CommandListDesc& desc);

            virtual void begin();
            virtual void end();

            virtual void setRenderState(IRenderState& state);
            virtual void setViewport(Viewport& viewport);
            virtual void setScissorRect(rect_t rect);
            virtual void setVertexBuffer(IVertexBuffer& buffer);
            virtual void setRenderTarget(IRenderTarget& target);
            
            virtual void clear(color_t color);
            virtual void draw(size_t, size_t, size_t, size_t);

            ID3D12CommandList&      getID3D12CommandList() { return *_list; }
            ID3D12CommandAllocator& getID3D12CommandAllocator() { return *_allocator; }
            ID3D12Device& getID3D12Device() { return _device->getID3D12Device(); }
            virtual IDevice& getDevice() { return *_device; }  

        private:
            D3D12DeviceImpl* _device;
            ID3D12GraphicsCommandList* _list;
            ID3D12CommandAllocator* _allocator;
            D3D12RenderTargetImpl* _target;
            D3D12RenderStateImpl* _renderState;
        };
    }
}