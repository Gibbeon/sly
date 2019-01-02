

#pragma once

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/resource.h"

namespace sly {
    namespace gfx {
    
        class D3D12RenderTargetImpl : public IRenderTarget {
        public:
            D3D12RenderTargetImpl() {}
            virtual void init(ID3D12Resource* ptr, size_t buffer){
                _resource = ptr;
                _bufferLocation = buffer;
            }

            virtual void write(void* data, size_t size, size_t stride) {
                
            }

            ID3D12Resource& getID3D12Resource() { return *_resource; }
            size_t getBufferLocation() {  return _bufferLocation; }
            size_t getSizeInBytes() {  return _sizeInBytes; }

        protected:

        private:
            ID3D12Resource* _resource;
            size_t _bufferLocation;
            size_t _sizeInBytes;
        };
    }
}
