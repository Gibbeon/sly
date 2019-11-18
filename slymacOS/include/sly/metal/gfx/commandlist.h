#pragma once

#include "sly/metal.h"
#include "sly/gfx/commandlist.h"
#include "sly/metal/gfx/device.h"
#include "sly/metal/gfx/renderstate.h"
#include "sly/metal/gfx/rendertarget.h"

namespace sly {
    namespace gfx {

        class METALDeviceImpl;

        class METALCommandListImpl: public ICommandList {
        public:
            METALCommandListImpl(METALDeviceImpl& device);
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

            //ID3D12CommandList&      getID3D12CommandList() { return *_list; }
            //ID3D12CommandAllocator& getID3D12CommandAllocator() { return *_allocator; }
            //ID3D12Device& getID3D12Device() { return _device->getID3D12Device(); }
            virtual IDevice& getDevice() { return *_device; }  

        private:
            METALDeviceImpl* _device;
            //ID3D12GraphicsCommandList* _list;
            //ID3D12CommandAllocator* _allocator;
            METALRenderTargetImpl* _target;
            METALRenderStateImpl* _renderState;
        };
    }
}