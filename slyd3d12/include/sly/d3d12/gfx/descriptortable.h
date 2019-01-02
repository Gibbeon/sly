
#pragma once
#include <vector>

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/managed.h"

namespace sly {
    namespace gfx {
        class D3D12DeviceImpl;

        struct D3D12DescriptorTableDesc {
        public:
            size_t capacity;

        };
        
        class D3D12DescriptorTableImpl : public D3D12ManagedImpl {
        public:
            D3D12DescriptorTableImpl(D3D12DeviceImpl& device);

            void init(D3D12DescriptorTableDesc& desc);

            void alloc(size_t* indicies, size_t count);
            void free(size_t*, size_t count);

            size_t getAt(size_t index);

            size_t getCapacity() { _capacity; }
            size_t getCount() { _count; }

        protected:
            using D3D12ManagedImpl::D3D12ManagedImpl;

            size_t _nextFree;
            size_t getNextFree();
        
        private:
            std::vector<bool_t> _used;
            size_t _capacity;
            size_t _count;

            ID3D12DescriptorHeap* _descHeap;
            size_t _descHeapStride;  
        };        

        class D3D12DescriptorTableBuilder : public Builder<D3D12DescriptorTableDesc> {
        public:
            D3D12DescriptorTableBuilder() : Builder({}) {}

            D3D12DescriptorTableBuilder& setCapacity(size_t capacity) { desc_.capacity = capacity; return *this; }

        };
    }
}

