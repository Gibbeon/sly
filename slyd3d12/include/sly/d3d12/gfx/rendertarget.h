

#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        class D3D12RenderTargetImpl : IRenderTarget {
        public:
            D3D12RenderTargetImpl() {}
            virtual void init(ID3D12Resource* ptr, size_t buffer){
                resource_ =ptr;
                bufferLocation_ = buffer;
            }

            virtual void write(ptr_t data, size_t size, size_t stride) {
                
            }

            ref_t<ID3D12Resource> getID3D12Resource() { return resource_; }
            size_t getBufferLocation() { return bufferLocation_; }
            size_t getSizeInBytes() { return sizeInBytes_; }

        protected:

        private:
            ref_t<ID3D12Resource> resource_;
            size_t bufferLocation_;
            size_t sizeInBytes_;
        };
    }
}
